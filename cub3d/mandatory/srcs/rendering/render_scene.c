/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 14:55:56 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** perform_dda:
** Steps through the grid using ray->side_dist and ray->delta_dist until
** we hit a wall. If side_dist.x < side_dist.y, we move in x direction
** (map.x += step_dir.x) and add delta_dist.x to side_dist.x. Otherwise,
** we move in y. We also set ray->side to 0 (x-side) or 1 (y-side). If
** the cell we land on is '1' (a wall), ray->hit = 1 and we stop.
*/
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

/*
** select_wall_texture:
** Chooses which wall texture (north, south, east, or west) is used based
** on the side of the collision (0 or 1) and the direction of the ray.
*/
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

/*
** draw_wall_column:
** Renders a single vertical slice of the wall at screen column x. We:
** 1) Pick the correct texture using select_wall_texture.
** 2) From draw_start to draw_end, compute which row in the texture to
**    sample. We then call get_tex_color and finally put_pixel to draw.
*/
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

/*
** fill_ceiling_and_floor:
** Fills the top half of the screen with ceiling_color and the bottom
** half with floor_color. These are simple vertical fills from row 0 to
** row (WIN_H/2)-1 for the ceiling, and from row (WIN_H/2) to WIN_H-1
** for the floor.
*/
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

/*
** render_scene:
** The main rendering function for raycasting. We:
** 1) Create a new (empty) image game->img.
** 2) Fill the entire screen with ceiling and floor colors.
** 3) For each vertical column 'x' on the screen, we:
**    - Build a ray from the player's position using init_ray.
**    - Use DDA (init_dda_ray & perform_dda) to find where the ray hits
**      a wall in the map.
**    - Calculate how tall that wall should appear, and which part of the
**      texture to use (calculate_ray_properties).
**    - Draw the vertical wall slice (draw_wall_column).
** 4) Finally, we put this assembled image on the window and destroy the
**    temporary image to free memory before the next frame.
*/
void	render_scene(t_game *game)
{
	t_ray	ray;
	int		x;

	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_size, &game->img.endian);
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
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->window->ptr, game->img.ptr, 0, 0);
	mlx_destroy_image(game->mlx, game->img.ptr);
}
