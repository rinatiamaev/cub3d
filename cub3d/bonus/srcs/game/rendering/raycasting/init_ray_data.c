/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:55:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 23:16:45 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
