/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:34:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 21:26:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Put a pixel into the main frame buffer (game->img) at (x, y).
*/
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
** Retrieves a pixel color from a given texture at texture coordinate (x, y).
** - No longer calls mlx_get_data_addr each time.
** - We assume x,y are within [0..(tex->size.x-1)] x [0..(tex->size.y-1)].
*/
static int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	pixel = tex->addr + (y * tex->line_size + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

/*
** Initializes the ray for a given screen column x.
** It computes the ray direction based on the camera plane.
*/
void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (double)WIN_W - 1.0;
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	ray->map.x = (int)game->player.pos.x;
	ray->map.y = (int)game->player.pos.y;
	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	ray->hit = false;
}

/*
** Initializes the DDA parameters for the ray.
** It computes the step direction and initial side distances.
*/
void	init_dda_ray(t_game *game, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_dir.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_dir.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_dir.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_dir.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y) * ray->delta_dist.y;
	}
}

/*
** Performs the DDA loop until a wall is hit.
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
** Calculates additional properties for the ray after DDA:
** perpendicular wall distance, line height, draw start/end, and initial texture mapping.
** We assume all wall textures share the same dimensions, e.g.:
**   int TEX_W  = game->tex.no.width;
**   int TEX_H = game->tex.no.height;
*/
void	calculate_ray_properties(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_w_dist = (ray->map.x - game->player.pos.x
				+ (1 - ray->step_dir.x) / 2.0) / ray->dir.x;
	else
		ray->perp_w_dist = (ray->map.y - game->player.pos.y
				+ (1 - ray->step_dir.y) / 2.0) / ray->dir.y;

	ray->line_height = (int)((double)WIN_H / ray->perp_w_dist);

	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;

	// Calculate where exactly the wall was hit (for texture X coordinate).
	if (ray->side == 0)
		ray->wall_x = game->player.pos.y + ray->perp_w_dist * ray->dir.y;
	else
		ray->wall_x = game->player.pos.x + ray->perp_w_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);

	// Initial tex.x depends on side & direction
	ray->tex.x = (int)(ray->wall_x * (double)TEX_W);
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.x = TEX_W - ray->tex.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.x = TEX_W - ray->tex.x - 1;

	// Calculate vertical step for each pixel and the initial texture position
	ray->step = (double)TEX_H / ray->line_height;
	ray->texPos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * ray->step;
}

/*
** Draws a vertical column (using wall texture) at screen column x.
** We pick which texture to use based on ray->side and ray->dir.
*/
void	draw_vertical_column(t_game *game, t_ray *ray, int x)
{
	t_texture *tex;

	// Pick the correct texture:
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			tex = &game->tex.ea;
		else
			tex = &game->tex.we;
	}
	else
	{
		if (ray->dir.y > 0)
			tex = &game->tex.so;
		else
			tex = &game->tex.no;
	}

	// Draw the wall slice from draw_start to draw_end
	int y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		// Use the texture's actual height here
		ray->tex.y = (int)ray->texPos & (tex->size.y - 1);
		ray->texPos += ray->step;

		int color = get_tex_color(tex, ray->tex.x, ray->tex.y);
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

/*
** Fills the ceiling (top half) and floor (bottom half).
*/
void	fill_ceiling_and_floor(t_img *img, int ceiling_color, int floor_color)
{
	int x, y;

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
** The main rendering function.
** 1) Create a new image (game->img).
** 2) Fill the background (ceiling/floor).
** 3) Cast rays for each column, drawing vertical slices of textured walls.
** 4) Display the final image, then destroy it.
*/
void	render_scene(t_game *game)
{
	t_ray	ray;
	int		x;

	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
		&game->img.bpp, &game->img.line_size, &game->img.endian);

	// Fill ceiling and floor
	fill_ceiling_and_floor(&game->img,
		game->map->conf.ceiling_color,
		game->map->conf.floor_color);

	// Raycast for each vertical strip
	x = 0;
	while (x < WIN_W)
	{
		init_ray(game, &ray, x);
		init_dda_ray(game, &ray);
		perform_dda(game, &ray);
		calculate_ray_properties(game, &ray);
		draw_vertical_column(game, &ray, x);
		x++;
	}

	// Show the result, then free the temporary image
	mlx_put_image_to_window(game->mlx, game->window->ptr, game->img.ptr, 0, 0);
	mlx_destroy_image(game->mlx, game->img.ptr);
}
