/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/26 21:16:50 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	perform_dda(t_game *game, t_ray *ray)
{
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
		if (game->map->matrix[ray->map.y][ray->map.x] == 1)
			ray->hit = 1;
	}
}

static t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
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

void	draw_wall_column(t_game *game, t_ray *ray, int x)
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
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

static void	fill_ceiling_and_floor(t_img *img, int ceiling_color,
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

void	render_scene(t_game *game)
{
	t_ray	ray;
	int		x;
	double	*z_buffer;

	z_buffer = x_calloc(game, WIN_W, sizeof(double));
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.line_size, &game->img.endian);
	fill_ceiling_and_floor(&game->img, game->map->conf.ceiling_color,
		game->map->conf.floor_color);
	x = 0;
	while (x < WIN_W)
	{
		init_ray(game, &ray, x);
		init_dda_ray(game, &ray);
		perform_dda(game, &ray);
		calculate_ray_properties(game, &ray);
		draw_wall_column(game, &ray, x);
		z_buffer[x++] = ray.perp_w_dist;
	}
	draw_sprites(game, game->player, z_buffer);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window->ptr, game->img.ptr, 0, 0);
	mlx_destroy_image(game->mlx, game->img.ptr);
	free(z_buffer);
}
