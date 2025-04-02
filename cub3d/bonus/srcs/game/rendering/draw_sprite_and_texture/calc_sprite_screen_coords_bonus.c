/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite_screen_coords_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:42:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 18:08:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Computes the horizontal screen position of a sprite.
 *
 * This function converts the sprite's camera-space coordinates into
 * screen space by projecting its `transform_x` (offset from the center)
 * and `transform_y` (depth) onto the screen's horizontal axis.
 *
 * The result is the X coordinate (in pixels) where the center of the
 * sprite should appear on the screen.
 *
 * Formula:
 *     screen_x = (screen_width / 2) * (1 + transform_x / transform_y)
 *
 * @param transform_x The horizontal offset in camera space.
 * @param transform_y The depth (distance to camera) in camera space.
 * @return The X coordinate of the sprite's center on screen.
 */
static int	get_sprite_screen_x(double transform_x, double transform_y)
{
	int	screen_center_x;

	screen_center_x = WIN_W >> 1;
	return ((int)(screen_center_x * (1 + transform_x / transform_y)));
}

/**
 * @brief Computes the on-screen size of a sprite based on its depth.
 *
 * This function calculates the vertical (and horizontal) size in pixels
 * that a sprite should appear on screen, based on its distance from the
 * player (`transform_y`). Closer sprites appear larger, and distant ones
 * appear smaller.
 *
 * The result is clamped to a minimum value of 1 pixel to ensure visibility.
 *
 * Formula:
 *     size = screen_height / transform_y
 *
 * @param transform_y The depth of the sprite in camera space.
 * @return The scaled dimension (in pixels) of the sprite on screen.
 */
static int	get_sprite_scaled_dimension(double transform_y)
{
	int	scaled_height;

	scaled_height = (int)fabs(WIN_H / transform_y);
	return (fmax(scaled_height, 1));
}

/**
 * @brief Calculates the vertical drawing bounds for a sprite.
 *
 * This function computes the Y-axis boundaries (top and bottom) of a sprite
 * on screen, centering it vertically based on its height. The coordinates are
 * clamped to the screen height to avoid drawing outside the visible area.
 *
 * The result is returned as a `t_point`, where:
 * - `x` is the top pixel (draw_start.y)
 * - `y` is the bottom pixel (draw_end.y)
 *
 * @param height The on-screen height of the sprite in pixels.
 * @return A point representing the vertical bounds (top and bottom Y values).
 */
static t_point	get_vertical_bounds(int height)
{
	t_point	vertical_bounds;

	vertical_bounds.y = clamp((WIN_H + height) / 2, 0, WIN_H - 1);
	vertical_bounds.x = clamp((WIN_H - height) / 2, 0, WIN_H - 1);
	return (vertical_bounds);
}

/**
 * @brief Calculates the horizontal drawing bounds for a sprite.
 *
 * This function determines the X-axis boundaries (left and right) of a
 * sprite on screen. It centers the sprite horizontally around `screen_x`
 * and clamps the result to the window width to keep it within visible bounds.
 *
 * The result is returned as a `t_point`, where:
 * - `x` is the left pixel (draw_start.x)
 * - `y` is the right pixel (draw_end.x)
 *
 * @param screen_x The horizontal center position of the sprite.
 * @param width The on-screen width of the sprite in pixels.
 * @return A point representing the horizontal bounds (left and right X values)
 */

static t_point	get_horizontal_bounds(int screen_x, int width)
{
	t_point	horizontal_bounds;

	horizontal_bounds.x = clamp(screen_x - width / 2, 0, WIN_W - 1);
	horizontal_bounds.y = clamp(screen_x + width / 2, 0, WIN_W - 1);
	return (horizontal_bounds);
}

/**
 * @brief Calculates the on-screen bounding box of the sprite.
 *
 * This function determines where the sprite should be drawn on screen based
 * on its position in camera space. It:
 *
 * 1. Computes the horizontal screen center of the sprite.
 * 2. Scales the sprite's width and height based on its depth.
 * 3. Calculates the vertical and horizontal bounds (top, bottom, left, right)
 *    of the sprite, centered around the projected position.
 * 4. Stores the draw boundaries in `data->draw_start` and `data->draw_end`.
 *
 * It returns `false` if the sprite would not be visible (zero or negative size
 * after clamping), and `true` otherwise.
 *
 * @param data Pointer to the sprite draw structure with projection data.
 * @return true if the sprite is within screen bounds and drawable,
 *         false otherwise.
 */
bool	calc_sprite_screen_coords(t_sprite_draw *data)
{
	t_point	vertical;
	t_point	horizontal;

	data->screen_x = get_sprite_screen_x(data->transform.x, data->transform.y);
	data->width = get_sprite_scaled_dimension(data->transform.y);
	data->height = data->width;
	vertical = get_vertical_bounds(data->height);
	horizontal = get_horizontal_bounds(data->screen_x, data->width);
	data->draw_start.y = vertical.x;
	data->draw_end.y = vertical.y;
	data->draw_start.x = horizontal.x;
	data->draw_end.x = horizontal.y;
	return (data->draw_start.x < data->draw_end.x
		&& data->draw_start.y < data->draw_end.y);
}
