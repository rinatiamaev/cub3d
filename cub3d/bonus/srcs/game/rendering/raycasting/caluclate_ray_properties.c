/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caluclate_ray_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:08:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/02 21:32:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_perpendicular_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_w_dist = (ray->map.x - game->player.pos.x
				+ (1 - ray->step_dir.x) / 2.0) / ray->dir.x;
	else
		ray->perp_w_dist = (ray->map.y - game->player.pos.y
				+ (1 - ray->step_dir.y) / 2.0) / ray->dir.y;
}

static	void	calculate_wall_projection(t_ray *ray)
{
	ray->line_height = (int)((double)WIN_H / ray->perp_w_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

static void	calculate_texture_mapping(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos.y + ray->perp_w_dist * ray->dir.y;
	else
		ray->wall_x = game->player.pos.x + ray->perp_w_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->hit == 2)
	{
		t_door *door = find_door_at(game, ray->map);
		if (door)
		{
			ray->wall_x += door->offset;
			if (ray->wall_x > 1.0)
				ray->wall_x = 1.0;
		}
	}
	ray->tex.x = (int)(ray->wall_x * (double)TEX_W);
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.x = TEX_W - ray->tex.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.x = TEX_W - ray->tex.x - 1;
	ray->step = (double)TEX_H / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2)
		* ray->step;
}

void	calculate_ray_properties(t_game *game, t_ray *ray)
{
	calculate_perpendicular_distance(game, ray);
	calculate_wall_projection(ray);
	calculate_texture_mapping(game, ray);
}
