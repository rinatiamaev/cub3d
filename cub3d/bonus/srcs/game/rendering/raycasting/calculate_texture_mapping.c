/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_texture_mapping.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:52:46 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:19:09 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	get_exact_wall_position(t_game *game, t_ray *ray)
{
	double	offset;
	double	wall_position;

	if (ray->side == 0)
	{
		offset = ray->perp_w_dist * ray->dir.y;
		wall_position = game->player.pos.y + offset;
	}
	else
	{
		offset = ray->perp_w_dist * ray->dir.x;
		wall_position = game->player.pos.x + offset;
	}
	return (wall_position);
}

static double	adjust_for_door_offset(t_game *game, t_ray *ray, double wall_x)
{
	t_door	*door;

	if (ray->hit == 2)
	{
		door = find_door_at(game, ray->map);
		if (door)
		{
			wall_x += door->offset;
			wall_x = wrap_in_range(wall_x, 1.0);
		}
	}
	return (wall_x);
}

static int	flip_texture_x_if_needed(t_ray *ray, int tex_x)
{
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = TEX_W - tex_x - 1;
	return (tex_x);
}

void	calculate_texture_mapping(t_game *game, t_ray *ray)
{
	double	exact_pos;
	double	wall_fraction;

	exact_pos = get_exact_wall_position(game, ray);
	wall_fraction = get_fractional_part(exact_pos);
	ray->wall_x = adjust_for_door_offset(game, ray, wall_fraction);
	ray->tex.x = (int)(ray->wall_x * (double)TEX_W);
	ray->tex.x = flip_texture_x_if_needed(ray, ray->tex.x);
	ray->step = (double)TEX_H / ray->line_height;
	ray->tex_pos
		= (ray->draw_start - (WIN_H >> 1) + (ray->line_height / 2)) * ray->step;
}
