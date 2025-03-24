/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:01:12 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:18:43 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	advance_dda_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step_dir.x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step_dir.y;
		ray->side = 1;
	}
}

static bool	is_wall_hit(t_game *game, t_ray *ray)
{
	if (ray->map.x < 0 || ray->map.x >= game->map->size.x
		|| ray->map.y < 0 || ray->map.y >= game->map->size.y)
	{
		ray->hit = 1;
		return (true);
	}
	if (game->map->matrix[ray->map.y][ray->map.x] == WALL)
	{
		ray->hit = 1;
		return (true);
	}
	return (false);
}

static bool	is_closed_door_hit(t_ray *ray, t_door *door)
{
	if (door && door->offset <= 0.0)
	{
		ray->hit = 2;
		return (true);
	}
	return (false);
}

static bool	is_partially_open_door_hit(t_game *game, t_ray *ray, t_door *door)
{
	double	door_x;

	if (!door || door->offset >= 1.0)
		return (false);
	if (ray->side == 0)
		door_x = game->player.pos.y + ((ray->map.x - game->player.pos.x
					+ (1 - ray->step_dir.x) / 2.0) / ray->dir.x) * ray->dir.y;
	else
		door_x = game->player.pos.x + ((ray->map.y - game->player.pos.y
					+ (1 - ray->step_dir.y) / 2.0) / ray->dir.y) * ray->dir.x;
	door_x -= floor(door_x);
	if (door_x < (1.0 - door->offset))
	{
		ray->hit = 2;
		return (true);
	}
	return (false);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	t_door	*door;

	while (ray->hit == 0)
	{
		advance_dda_step(ray);
		if (is_wall_hit(game, ray))
			break ;
		if (game->map->matrix[ray->map.y][ray->map.x] == DOOR
			|| game->map->matrix[ray->map.y][ray->map.x] == EXIT_DOOR)
		{
			door = find_door_at(game, ray->map);
			if (is_closed_door_hit(ray, door)
				|| is_partially_open_door_hit(game, ray, door))
				break ;
		}
	}
}
