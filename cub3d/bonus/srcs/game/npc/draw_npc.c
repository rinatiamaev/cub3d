/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:05:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/25 10:47:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


/*   get_current_npc_frame
 *   Computes the current animation frame for the NPC based on elapsed
 *   time. It uses gettimeofday() to measure how many milliseconds have
 *   passed since the NPC animation started (npc->anim_start) and then
 *   calculates the frame index using the provided frame_duration_ms.
 */
static int	get_current_npc_frame(t_npc *npc, int frame_duration_ms)
{
	struct timeval	tv;
	long			current_time;
	long			elapsed_ms;
	int				frame_index;

	// Get current time in microseconds.
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000000L + tv.tv_usec;
	
	// Calculate elapsed time (in milliseconds) since animation start.
	elapsed_ms = (current_time - npc->anim_start) / 1000;
	
	// Calculate the frame index by dividing elapsed time by frame duration,
	// then take modulo the number of frames.
	frame_index = (elapsed_ms / frame_duration_ms) % npc->num_frames;
	return (frame_index);
}

/*   draw_texture_at_scaled
 *   Draws a scaled version of a texture (tex) onto the game image (game->img)
 *   using precomputed sprite properties (props) and a z-buffer for occlusion.
 *   - props->size contains the scaled width and height of the sprite.
 *   - props->screen contains the top-left screen coordinates where the sprite
 *     should be drawn.
 *   - props->depth is used for comparing against the z-buffer to occlude
 *     sprite pixels behind walls.
 *   - The function uses fixed-point arithmetic (with shifts by 8) to compute
 *     scaling steps (step.x and step.y) for the texture coordinates.
 */
static void	draw_texture_at_scaled(t_game *game, t_texture *tex,
	t_sprite_props *props, double *z_buffer)
{
	t_sprite_draw_ctx	ctx;
	int					x;
	int					y;

	// Calculate fixed-point scaling steps for texture Y and X
	// based on the sprite's scaled size (props->size).
	ctx.step.y = tex->size.y * 256 / props->size.y;
	ctx.step.x = tex->size.x * 256 / props->size.x;
	ctx.tex_pos_y = 0; // Initialize the texture vertical position accumulator

	y = 0;
	while (y < props->size.y)
	{
		// Compute current texture Y coordinate from the fixed-point accumulator.
		ctx.tex.y = (ctx.tex_pos_y >> 8) & (tex->size.y - 1);
		ctx.tex_pos_y += ctx.step.y;
		
		x = 0;
		while (x < props->size.x)
		{
			// Calculate the current screen x position for this pixel column.
			ctx.current_screen_x = props->screen.x + x;
			// Skip drawing if outside screen bounds.
			if (ctx.current_screen_x < 0 || ctx.current_screen_x >= WIN_W)
			{
				x++;
				continue;
			}
			// Compute current texture X coordinate using fixed-point arithmetic.
			ctx.tex.x = (x * ctx.step.x) >> 8;
			// Retrieve the color from the texture at (tex.x, tex.y).
			ctx.color = get_tex_color(tex, ctx.tex.x, ctx.tex.y);
			
			// Check transparency: here we assume the value 42 represents transparency.
			if (ctx.color != 42)
			{
				// Only draw the pixel if the sprite is closer than the wall (using z-buffer).
				if (props->depth < z_buffer[ctx.current_screen_x])
					put_pixel(&game->img, ctx.current_screen_x,
						props->screen.y + y, ctx.color);
			}
			x++;
		}
		y++;
	}
}

/*   compute_sprite_props
 *   Computes all the necessary properties for rendering the NPC sprite:
 *   - Transformed coordinates in camera space (props->transform)
 *   - Depth (props->depth), which is used for scaling and occlusion
 *   - The final size (props->size) of the sprite when drawn on screen
 *   - The screen position (props->screen) where the sprite will be placed
 *   Returns true if the sprite is visible, false otherwise.
 */
static bool	compute_sprite_props(t_game *game, t_npc *npc,
		t_sprite_props *props)
{
	double		det, inv_det;
	t_dpoint	sprite;

	// Translate NPC world position relative to the player's position.
	sprite.x = npc->pos.x - game->player.pos.x;
	sprite.y = npc->pos.y - game->player.pos.y;

	// Compute the determinant of the camera matrix.
	det = game->player.plane.x * game->player.dir.y -
	      game->player.dir.x * game->player.plane.y;
	// Prevent division by a very small number.
	if (fabs(det) < 1e-6)
		return (false);
	inv_det = 1.0 / det;

	// Transform NPC position to camera space.
	props->transform.x = inv_det * (game->player.dir.y * sprite.x -
	                       game->player.dir.x * sprite.y);
	props->transform.y = inv_det * (-game->player.plane.y * sprite.x +
	                       game->player.plane.x * sprite.y);
	props->depth = props->transform.y;

	// If the NPC is behind the player or too close, it is not visible.
	if (props->depth <= 0.1)
		return (false);

	// Compute the sprite's scaled height and width on screen.
	props->size.y = abs((int)(WIN_H / props->depth));
	props->size.x = (props->size.y * TEX_W) / TEX_H;
	
	// Calculate vertical offset to center the sprite on screen.
	props->screen.y = (WIN_H - props->size.y) / 2;
	// Calculate horizontal screen position using the transformed x value.
	props->screen.x = (int)((WIN_W / 2.0) * (1 + props->transform.x / props->depth));
	return (true);
}

/*   draw_npc
 *   Renders the NPC sprite with occlusion by performing the following steps:
 *   1. Compute sprite properties (transformed coordinates, size, screen
 *      position, and depth) using compute_sprite_props().
 *   2. Determine the current animation frame based on elapsed time.
 *   3. Retrieve the corresponding texture from npc->idle_frames.
 *   4. Draw the scaled texture with occlusion checks using the provided
 *      z-buffer via draw_texture_at_scaled().
 */
void	draw_npc(t_game *game, t_npc *npc, double *z_buffer)
{
	int				frame;
	t_texture		*tex;
	t_sprite_props	props;

	// Compute all necessary properties for rendering the NPC sprite.
	// If the NPC is not visible, exit early.
	if (!compute_sprite_props(game, npc, &props))
		return;
	
	// Get the current animation frame (using a frame duration of 200ms).
	frame = get_current_npc_frame(npc, 200);
	tex = &npc->idle_frames[frame];
	
	// Draw the NPC sprite with scaling and occlusion.
	draw_texture_at_scaled(game, tex, &props, z_buffer);
}
