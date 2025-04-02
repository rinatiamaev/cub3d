/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_splash_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:13:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 18:46:50 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Updates the player's splash screen animation over time.
 *
 * This function advances the current frame of the splash animation based on
 * the elapsed `delta_time`. It operates in milliseconds and uses a fixed
 * frame duration (`anim_speed_ms`) of 100 ms.
 *
 * When the timer exceeds the frame duration:
 * - The animation frame index is incremented.
 * - If the animation reaches the end of the frame sequence, it resets
 *   the index to 0 and disables the splash state (`is_splashing = false`).
 *
 * This function ensures smooth timed transitions between splash frames.
 *
 * @param player Pointer to the player (holds animation state).
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
static inline void	update_splash_animation(t_player *player,
											double delta_time)
{
	const double	anim_speed_ms = 100.0;

	player->sprite.anim_timer += delta_time * 1000.0;
	if (player->sprite.anim_timer >= anim_speed_ms)
	{
		player->sprite.anim_timer -= anim_speed_ms;
		player->sprite.anim_index++;
		if (player->sprite.anim_index >= player->sprite.splash_frames_count)
		{
			player->sprite.anim_index = 0;
			player->is_splashing = false;
		}
	}
}

/**
 * @brief Calculates the screen position to draw the splash frame.
 *
 * This function computes the top-left corner on screen where the splash
 * texture should be drawn. It:
 * - Horizontally centers the frame within the window.
 * - Vertically aligns the frame to the bottom of the screen.
 *
 * This ensures the splash animation appears centered and grounded at the
 * bottom edge of the view.
 *
 * @param frame Pointer to the splash frame texture.
 * @return The screen-space position to start drawing the frame.
 */

static inline t_point	get_splash_draw_position(t_texture *frame)
{
	t_point	pos;

	pos.x = (WIN_W - frame->size.x) / 2;
	pos.y = WIN_H - frame->size.y;
	return (pos);
}

/**
 * @brief Retrieves the color of a texture pixel with basic transparency.
 *
 * This function fetches the color at pixel (x, y) from the given texture.
 * It includes safety and transparency checks:
 *
 * - If the coordinates are out of bounds, it returns `42` (used as a special
 *   value to skip drawing).
 * - If the pixel color is pure black (`0x000000`), it is treated as
 *   transparent and also returns `42`.
 *
 * This behavior is useful for rendering textures with a "magic color"
 * transparency mask.
 *
 * @param tex Pointer to the texture.
 * @param x X coordinate within the texture.
 * @param y Y coordinate within the texture.
 * @return The pixel color, or `42` to indicate transparency.
 */
static inline unsigned int	get_tex_color(t_texture *tex, int x, int y)
{
	unsigned int	*pixel_ptr;
	unsigned int	color;

	if (x < 0 || x >= tex->size.x || y < 0 || y >= tex->size.y)
		return (42);
	pixel_ptr
		= (unsigned int *)(tex->addr + y * tex->line_size + x
			* (tex->bpp >> 3));
	color = *pixel_ptr;
	if ((color & 0x00FFFFFF) == 0x000000)
		return (42);
	return (color);
}

/**
 * @brief Draws a splash animation frame to the screen at a given position.
 *
 * This function renders the entire splash texture onto the screen’s image
 * buffer, starting at the given top-left `start` position. For each pixel:
 *
 * - It fetches the color using `get_tex_color`.
 * - If the color is not the magic transparent value (42 or pure black),
 *   the pixel is drawn directly into the framebuffer.
 *
 * It uses per-pixel drawing with manual buffer offset computation to
 * maintain full control over placement and transparency.
 *
 * @param game Pointer to the game state (provides access to the image buffer).
 * @param frame Pointer to the splash frame texture to draw.
 * @param start Top-left corner of where to render the texture on screen.
 */
static inline void	draw_splash_frame(t_game *game, t_texture *frame,
													t_point start)
{
	int				x;
	int				y;
	char			*dst;
	unsigned int	color;

	y = 0;
	while (y < frame->size.y)
	{
		x = 0;
		dst = game->img.addr + ((start.y + y) * game->img.line_size)
			+ (start.x * (game->img.bpp >> 3));
		while (x < frame->size.x)
		{
			color = get_tex_color(frame, x, y);
			if ((color & 0x00FFFFFF) != 42)
				*(unsigned int *)dst = color;
			dst += (game->img.bpp >> 3);
			x++;
		}
		y++;
	}
}

/**
 * @brief Renders the current splash animation frame if active.
 *
 * This function handles the logic and rendering of the player's splash
 * animation (e.g., when using a bucket of water). If the splash state
 * is active (`is_splashing`), it:
 *
 * 1. Updates the animation timer and frame index.
 * 2. Retrieves the current splash frame texture.
 * 3. Computes the position to draw the frame (centered at bottom of screen).
 * 4. Draws the frame using per-pixel rendering with transparency support.
 *
 * If the splash animation has finished, it is automatically disabled.
 *
 * @param game Pointer to the game state (includes render target).
 * @param player Pointer to the player (holds splash animation state).
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
void	draw_splash(t_game *game, t_player *player, double delta_time)
{
	t_texture	*splash_frame;
	t_point		start;

	if (!player->is_splashing)
		return ;
	update_splash_animation(player, delta_time);
	splash_frame = &player->sprite.splash_frames[player->sprite.anim_index];
	start = get_splash_draw_position(splash_frame);
	draw_splash_frame(game, splash_frame, start);
}
