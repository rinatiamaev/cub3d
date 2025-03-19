/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:05:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/19 10:21:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	t_door	*door;
	
	if (ray->hit == 2)
	{
		door = find_door_at(game, ray->map);
		if (door && door->type == EXIT_DOOR_TYPE)
			return (&game->tex.exit_door);
		return (&game->tex.door);
	}
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
