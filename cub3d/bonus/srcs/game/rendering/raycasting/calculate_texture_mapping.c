/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_texture_mapping.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:52:46 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 10:53:13 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	get_exact_wall_position(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		return (game->player.pos.y + ray->perp_w_dist * ray->dir.y);
	else
		return (game->player.pos.x + ray->perp_w_dist * ray->dir.x);
}

static double	adjust_for_door_offset(t_game *game, t_ray *ray,
														double wall_x)
{
	t_door	*door;

	if (ray->hit == 2)
	{
		door = find_door_at(game, ray->map);
		if (door)
		{
			wall_x += door->offset;
			if (wall_x < 0.0)
				wall_x += 1.0;
			if (wall_x > 1.0)
				wall_x -= 1.0;
		}
	}
	return (wall_x);
}

void	calculate_texture_mapping(t_game *game, t_ray *ray)
{
	double	exact_pos;

	exact_pos = get_exact_wall_position(game, ray);
	ray->wall_x
		= adjust_for_door_offset(game, ray, exact_pos - floor(exact_pos));
	ray->tex.x = (int)(ray->wall_x * (double)TEX_W);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		ray->tex.x = TEX_W - ray->tex.x - 1;
	ray->step = (double)TEX_H / ray->line_height;
	ray->tex_pos
		= (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * ray->step;
}
