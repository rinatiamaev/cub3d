/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caluclate_ray_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:08:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:19:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	compute_perpendicular_wall_distance(t_game *game, t_ray *ray)
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

static int	compute_wall_line_height(double perp_distance)
{
	double	scaled_height;

	scaled_height = (double)WIN_H / perp_distance;
	return ((int)scaled_height);
}

static void	compute_wall_bounds_on_screen(t_ray *ray)
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

void	calculate_ray_properties(t_game *game, t_ray *ray)
{
	ray->perp_w_dist = compute_perpendicular_wall_distance(game, ray);
	ray->line_height = compute_wall_line_height(ray->perp_w_dist);
	compute_wall_bounds_on_screen(ray);
	calculate_texture_mapping(game, ray);
}
