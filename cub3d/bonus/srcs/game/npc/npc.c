/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:05:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/21 13:40:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_dpoint	transform_npc(t_game *game, t_npc *npc, double *transformY)
{
	t_dpoint	sprite;
	t_dpoint	transform;
	double		invDet;

	sprite.x = npc->pos.x - game->player.pos.x;
	sprite.y = npc->pos.y - game->player.pos.y;
	invDet = 1.0 / (game->player.plane.x * game->player.dir.y -
		game->player.dir.x * game->player.plane.y);
	transform.x = invDet * (game->player.dir.y * sprite.x -
		game->player.dir.x * sprite.y);
	transform.y = invDet * (-game->player.plane.y * sprite.x +
		game->player.plane.x * sprite.y);
	*transformY = transform.y;
	return (transform);
}

/*
** get_current_npc_frame:
** Uses gettimeofday to compute the elapsed time since the NPC's 
** animation started. Given frame_duration_ms, returns a frame index.
*/
static int	get_current_npc_frame(t_npc *npc, int frame_duration_ms)
{
	struct timeval	tv;
	long			current_time;
	long			elapsed_ms;
	int				frame_index;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000000L + tv.tv_usec;
	elapsed_ms = (current_time - npc->anim_start) / 1000;
	frame_index = (elapsed_ms / frame_duration_ms) % npc->num_frames;
	return (frame_index);
}

static bool	is_npc_visible(t_game *game, t_npc *npc, double *transformY)
{
	t_dpoint	sprite;
	double		invDet;
	t_dpoint	transform;

	// Translate NPC position relative to player
	sprite.x = npc->pos.x - game->player.pos.x;
	sprite.y = npc->pos.y - game->player.pos.y;

	// Compute inverse determinant of camera matrix
	invDet = 1.0 / (game->player.plane.x * game->player.dir.y - game->player.dir.x * game->player.plane.y);

	// Transform NPC position to camera space
	transform.x = invDet * (game->player.dir.y * sprite.x - game->player.dir.x * sprite.y);
	transform.y = invDet * (-game->player.plane.y * sprite.x + game->player.plane.x * sprite.y);
	*transformY = transform.y;

	// If NPC is behind the player, don't render it
	return (*transformY > 0);
}

static void	compute_sprite_screen(double transformX, double transformY,
	int *spriteScreenX, int *spriteHeight, int *spriteScreenY)
{
	// Compute sprite height (scaling factor based on distance)
	*spriteHeight = abs((int)(WIN_H / transformY));
	*spriteScreenY = (WIN_H - *spriteHeight) / 2;

	// Correctly compute the screen X coordinate
	*spriteScreenX = (int)((WIN_W / 2) * (1 + transformX / transformY));
}

static void	draw_texture_at_scaled(t_game *game, t_texture *tex,
	int screen_x, int screen_y, int spriteHeight)
{
	int spriteWidth = (tex->size.x * spriteHeight) / tex->size.y;
	int texX, texY, x, y, color;
	int stepY = tex->size.y * 256 / spriteHeight;  // Fixed-point scaling
	int stepX = tex->size.x * 256 / spriteWidth;
	int texPosY = 0;

	for (y = 0; y < spriteHeight; y++)
	{
		texY = (texPosY >> 8) & (tex->size.y - 1);
		texPosY += stepY;

		for (x = 0; x < spriteWidth; x++)
		{
			texX = (x * stepX) >> 8;
			color = get_tex_color(tex, texX, texY);

			// Skip fully transparent pixels (assuming 0x000000 is transparent)
			if (color != 42)
				put_pixel(&game->img, screen_x + x, screen_y + y, color);
		}
	}
}

void	draw_npc(t_game *game, t_npc *npc)
{
	int			frame;
	t_texture	*tex;
	t_dpoint	transform;
	double		transformY;
	int			spriteScreenX, spriteHeight, spriteScreenY;

	// Check if the NPC is visible before rendering
	if (!is_npc_visible(game, npc, &transformY))
		return;

	// Get current animation frame (e.g., 200ms per frame)
	frame = get_current_npc_frame(npc, 200);
	tex = &npc->idle_frames[frame];

	// Transform NPC world position to camera space
	transform = transform_npc(game, npc, &transformY);
	if (transformY <= 0 || transformY < 0.1)
    	return ;  // NPC is behind the player, don't render it

	// Compute correct sprite screen position & size
	compute_sprite_screen(transform.x, transformY, &spriteScreenX, &spriteHeight, &spriteScreenY);

	// Draw the NPC
	draw_texture_at_scaled(game, tex, spriteScreenX, spriteScreenY, spriteHeight);
}