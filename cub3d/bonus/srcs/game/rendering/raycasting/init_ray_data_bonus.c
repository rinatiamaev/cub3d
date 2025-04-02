/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_data_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:55:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 14:21:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes the ray's direction and delta distances for DDA.
 *
 * This function computes the direction of a ray for the current vertical
 * screen stripe `x` based on the player's facing direction and the camera
 * plane. It also determines which grid square the ray starts in, and
 * precomputes the delta distances (distance to next side in the grid for
 * DDA traversal in X and Y). These values are essential for the DDA step
 * in raycasting.
 *
 * @param game Pointer to the game state, containing player data.
 * @param ray Pointer to the ray structure to be initialized.
 * @param x The current screen column index (from 0 to WIN_W - 1).
 */

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (double)WIN_W - 1.0;
	ray->dir.x
		= game->player.facing_dir.x + game->player.view_plane.x * camera_x;
	ray->dir.y
		= game->player.facing_dir.y + game->player.view_plane.y * camera_x;
	ray->map.x = (int)game->player.pos.x;
	ray->map.y = (int)game->player.pos.y;
	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	ray->hit = false;
}

/**
 * @brief Initializes step direction and initial side distances for DDA.
 *
 * Based on the direction of the ray, this function determines in which
 * direction to step in the grid (either -1 or 1 for both x and y). It also
 * calculates the initial side distances from the player's position to the
 * first grid boundary in both x and y directions. These values are used by
 * the DDA algorithm to incrementally step through the map grid.
 *
 * @param game Pointer to the game state (provides player position).
 * @param ray Pointer to the ray structure containing direction and map data.
 */
void	init_dda_ray(t_game *game, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_dir.x = -1;
		ray->side_dist.x
			= (game->player.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_dir.x = 1;
		ray->side_dist.x
			= (ray->map.x + 1.0 - game->player.pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_dir.y = -1;
		ray->side_dist.y
			= (game->player.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_dir.y = 1;
		ray->side_dist.y
			= (ray->map.y + 1.0 - game->player.pos.y) * ray->delta_dist.y;
	}
}
