/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_column_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:22:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 18:19:36 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Determines whether the current sprite stripe should be rendered.
 *
 * This function performs visibility checks for the current vertical stripe
 * of the sprite before drawing:
 *
 * 1. It ensures the sprite is in front of the player (`transform.y > 0`).
 * 2. It verifies that the current screen column (`stripe_x`) is within
 *    the visible screen width.
 * 3. It compares the sprite's depth (`transform.y`) against the Z-buffer
 *    at the current column to ensure the sprite isn't occluded by a wall.
 *
 * If all checks pass, the stripe is considered visible and should be drawn.
 *
 * @param data Pointer to the sprite draw data.
 * @param z_buffer Array of wall depths for each vertical screen column.
 * @return true if the stripe should be rendered, false otherwise.
 */
static inline bool	is_sprite_stripe_visible(t_sprite_draw *data,
															double *z_buffer)
{
	if (data->transform.y <= 0)
		return (false);
	if (data->stripe_x < 0 || data->stripe_x >= WIN_W)
		return (false);
	if (data->transform.y >= z_buffer[data->stripe_x])
		return (false);
	return (true);
}

/**
 * @brief Calculates the horizontal texture coordinate for a sprite stripe.
 *
 * This function maps a vertical stripe on the screen (`stripe_x`) to the
 * corresponding X coordinate within the sprite's texture image.
 *
 * It does this by computing the relative horizontal position of the stripe
 * within the on-screen sprite bounds, and scaling it to the texture width.
 *
 * This ensures that the correct vertical slice of the texture is sampled
 * when rendering the sprite.
 *
 * @param stripe_x The current screen X coordinate of the sprite stripe.
 * @param screen_x The screen X position of the sprite center.
 * @param sprite_width The width of the sprite on screen (in pixels).
 * @param texture_width The width of the sprite texture (in pixels).
 * @return The X coordinate to sample from the texture.
 */
static inline int	calc_tex_pixel_x(int stripe_x, int screen_x,
										int sprite_width, int texture_width)
{
int	relative_x;

relative_x = stripe_x - (-sprite_width / 2 + screen_x);
return ((relative_x * texture_width) / sprite_width);
}

/**
 * @brief Calculates the vertical texture coordinate for a sprite pixel.
 *
 * This function maps a screen Y position (`screen_y`) within a sprite's
 * projected height to the corresponding Y coordinate in the sprite's texture.
 *
 * The calculation uses fixed-point arithmetic (shifted by 8 bits) for better
 * precision during the scaling process without using floating-point math.
 *
 * This ensures that the sprite's texture is sampled correctly regardless of
 * its on-screen height.
 *
 * @param screen_y The current screen Y coordinate being drawn.
 * @param sprite_height The height of the sprite on screen (in pixels).
 * @param texture_height The height of the sprite texture (in pixels).
 * @return The Y coordinate to sample from the texture.
 */
static inline int	get_texture_y(int screen_y, int sprite_height,
															int texture_height)
{
	int		offset;
	int		texture_y;

	offset = screen_y - (WIN_H >> 1) + (sprite_height >> 1);
	offset = (int)(((int64_t)offset) << 8);
	texture_y
		= (int)((((int64_t)offset * texture_height) / sprite_height) >> 8);
	return (texture_y);
}

/**
 * @brief Retrieves the color of a texture pixel with basic transparency check.
 *
 * This function returns the color value at coordinates (x, y) in the texture.
 * It includes two safeguards:
 *
 * 1. If the coordinates are out of bounds, it returns a special fallback value
 *    (`42`) to signal that the pixel should not be drawn.
 * 2. If the pixel color is pure black (`0x000000`), it is treated as
 *    transparent and also returns `42`.
 *
 * The returned value is used during sprite rendering to skip drawing
 * transparent or invalid pixels.
 *
 * @param tex Pointer to the texture structure.
 * @param x X coordinate within the texture.
 * @param y Y coordinate within the texture.
 * @return The color value, or 42 to indicate transparency or invalid access.
 */
static inline unsigned int	get_tex_color(t_texture *tex, int x, int y)
{
	unsigned int	*pixel_ptr;
	unsigned int	color;

	if (x < 0 || x >= tex->size.x || y < 0 || y >= tex->size.y)
		return (42);
	pixel_ptr
		= (unsigned int *)(tex->addr + y
			* tex->line_size + x * (tex->bpp >> 3));
	color = *pixel_ptr;
	if ((color & 0x00FFFFFF) == 0x000000)
		return (42);
	return (color);
}

/**
 * @brief Renders a single vertical stripe (column) of a sprite to the screen.
 *
 * This function draws one vertical stripe of a sprite onto the screen's image
 * buffer. It performs the following steps:
 *
 * 1. Checks if the stripe is visible (in front of the player and not occluded
 *    by walls) using the Z-buffer.
 * 2. Calculates the corresponding X coordinate in the sprite texture using
 *    perspective-correct scaling.
 * 3. Iterates over each pixel in the vertical range of the sprite's bounding
 *    box, computing the matching Y texture coordinate.
 * 4. Retrieves the texture color, applying basic transparency (color 42 or
 *    pure black).
 * 5. Writes the pixel color to the correct position in the screen buffer.
 *
 * This function is called for each stripe (`stripe_x`) of a sprite within
 * the visible range.
 *
 * @param game Pointer to the game state, including the image buffer.
 * @param data Pointer to the current sprite draw state and texture info.
 * @param z_buffer Array containing wall distances for depth comparison.
 */
void	draw_sprite_column(t_game *game, t_sprite_draw *data, double *z_buffer)
{
	t_point			screen_pos;
	char			*dst;
	unsigned int	color;

	if (!is_sprite_stripe_visible(data, z_buffer))
		return ;
	data->tex_pixel.x = calc_tex_pixel_x(data->stripe_x, data->screen_x,
			data->width, data->texture->size.x);
	screen_pos.x = data->stripe_x;
	screen_pos.y = data->draw_start.y;
	dst = game->img.addr + (screen_pos.y * game->img.line_size)
		+ (screen_pos.x * (game->img.bpp >> 3));
	while (screen_pos.y < data->draw_end.y)
	{
		data->tex_pixel.y = get_texture_y(screen_pos.y, data->height,
				data->texture->size.y);
		color
			= get_tex_color
			(data->texture, data->tex_pixel.x, data->tex_pixel.y);
		if ((color & 0x00FFFFFF) != 42)
			*(unsigned int *)dst = color;
		dst += game->img.line_size;
		screen_pos.y++;
	}
}
