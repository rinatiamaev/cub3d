/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caluclate_ray_properties_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:08:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 14:43:22 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Computes the perpendicular distance from the player to the wall.
 *
 * This function calculates the perpendicular distance from the player to
 * the point where the ray hit a wall. The result is used to avoid the fisheye
 * effect when projecting wall slices to the screen.
 *
 * Depending on whether the ray hit a vertical (side == 0) or horizontal
 * (side == 1) wall, it calculates the distance along the X or Y axis,
 * adjusting by half a grid step when stepping in the negative direction.
 *
 * @param game Pointer to the game state (for player position).
 * @param ray Pointer to the ray structure with map and direction data.
 * @return The perpendicular distance from the player to the wall.
 */
static inline double	compute_perpendicular_wall_distance(t_game *game,
																t_ray *ray)
{
	double	distance;
	double	player_to_wall;
	double	half_step;

	if (ray->side == 0)
	{
		player_to_wall = ray->map.x - game->player.pos.x;
		half_step = (1.0 - ray->step_dir.x) / 2.0;
		distance = (player_to_wall + half_step) / ray->dir.x;
	}
	else
	{
		player_to_wall = ray->map.y - game->player.pos.y;
		half_step = (1.0 - ray->step_dir.y) / 2.0;
		distance = (player_to_wall + half_step) / ray->dir.y;
	}
	return (distance);
}

/**
 * @brief Computes the projected wall height on screen.
 *
 * This function calculates the vertical height (in pixels) of the wall slice
 * to render based on the perpendicular distance from the player to the wall.
 * A smaller distance results in a taller wall (closer to the player), and
 * vice versa. This is a core part of the perspective projection in raycasting.
 *
 * @param perp_distance The perpendicular distance from the player to the wall.
 * @return The height in pixels of the wall line to draw on screen.
 */
static inline int	compute_wall_line_height(double perp_distance)
{
	double	scaled_height;

	scaled_height = (double)WIN_H / perp_distance;
	return ((int)scaled_height);
}

/**
 * @brief Computes the vertical start and end positions for the wall slice.
 *
 * Based on the projected wall height, this function calculates the top and
 * bottom Y-coordinates of the wall column to draw on screen. It centers the
 * wall vertically and clamps the values to the visible screen area to avoid
 * drawing outside the window bounds.
 *
 * The results are stored in `ray->draw_start` and `ray->draw_end`.
 *
 * @param ray Pointer to the ray containing the computed wall height.
 */
static inline void	compute_wall_bounds_on_screen(t_ray *ray)
{
	double	min;
	double	max;
	double	top_boundary;
	double	bottom_boundary;

	min = 0;
	max = WIN_H - 1;
	top_boundary = -ray->line_height / 2 + (WIN_H >> 1);
	bottom_boundary = ray->line_height / 2 + (WIN_H >> 1);
	ray->draw_start = (int)clamp(top_boundary, min, max);
	ray->draw_end = (int)clamp(bottom_boundary, min, max);
}

/**
 * @brief Computes all rendering properties for a ray after a wall hit.
 *
 * This function prepares all necessary data to render a vertical wall slice
 * on screen after a ray has hit a wall. It performs the following steps:
 *
 * 1. Computes the perpendicular distance from the player to the wall,
 *    correcting for the fisheye effect.
 * 2. Calculates the projected height of the wall slice based on distance.
 * 3. Determines the vertical screen bounds to draw the wall slice.
 * 4. Computes the texture mapping parameters for accurate sampling.
 *
 * These computed values are stored in the `ray` structure for use in the
 * rendering phase.
 *
 * @param game Pointer to the game state (provides player position).
 * @param ray Pointer to the ray structure to be filled with rendering data.
 */
void	calculate_ray_properties(t_game *game, t_ray *ray)
{
	ray->perp_w_dist = compute_perpendicular_wall_distance(game, ray);
	ray->line_height = compute_wall_line_height(ray->perp_w_dist);
	compute_wall_bounds_on_screen(ray);
	calculate_texture_mapping(game, ray);
}
