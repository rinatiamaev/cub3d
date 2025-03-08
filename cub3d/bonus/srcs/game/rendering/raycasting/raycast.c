/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:05:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/08 02:05:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	perform_dda(t_game *game, t_ray *ray)
{
	t_door	*door;
	double	door_x;

	while (ray->hit == 0)
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
		if (game->map->matrix[ray->map.y][ray->map.x] == WALL)
			ray->hit = 1;
		else if (game->map->matrix[ray->map.y][ray->map.x] == DOOR)
		{
			door = find_door_at(game, ray->map);
			if (door)
			{
				if (door->offset >= 1.0)
					continue ;
				else if (door->offset <= 0.0)
				{
					ray->hit = 2;
					break ;
				}
				else
				{
					if (ray->side == 0)
						door_x = game->player.pos.y + ((ray->map.x - game->player.pos.x + (1 - ray->step_dir.x) / 2.0) / ray->dir.x) * ray->dir.y;
					else
						door_x = game->player.pos.x + ((ray->map.y - game->player.pos.y + (1 - ray->step_dir.y) / 2.0) / ray->dir.y) * ray->dir.x;
					door_x -= floor(door_x);
					if (door_x < (1.0 - door->offset))
					{
						ray->hit = 2;
						break ;
					}
					else
						continue ;
				}
			}
		}
	}
}

static t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->hit == 2)
		return (&game->tex.door);
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (&game->tex.ea);
		else
			return (&game->tex.we);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->tex.so);
		else
			return (&game->tex.no);
	}
}

void	draw_wall_column(t_game *game, t_ray *ray, int *x)
{
	t_texture	*tex;
	int			y;
	int			color;

	tex = select_wall_texture(game, ray);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (tex->size.y - 1);
		ray->tex_pos += ray->step;
		color = get_tex_color(tex, ray->tex.x, ray->tex.y);
		if (color != 42)
			put_pixel(&game->img, *x, y, color);
		y++;
	}
}

void	fill_ceiling_and_floor(t_img *img, int ceiling_color,
												int floor_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	raycast(t_game *game, t_ray *ray, int *x, double *z_buffer)
{
	init_ray(game, ray, *x);
	init_dda_ray(game, ray);
	perform_dda(game, ray);
	calculate_ray_properties(game, ray);
	draw_wall_column(game, ray, x);
	z_buffer[(*x)++] = ray->perp_w_dist;
}
