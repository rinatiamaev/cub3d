/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:34:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 14:48:48 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Put a pixel into the main frame buffer (game->img) at (x, y).
*/
void	put_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return;
	char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
** Retrieves a pixel color from a given texture at texture coordinate (x, y).
** - No longer calls mlx_get_data_addr each time.
** - We assume x,y are within [0..(tex->width-1)] x [0..(tex->height-1)].
*/
static int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

/*
** Initializes the ray for a given screen column x.
** It computes the ray direction based on the camera plane.
*/
void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	cameraX;

	cameraX = 2.0 * (double)x / (double)WIN_W - 1.0;
	ray->rayDir.x = game->player.dir.x + game->player.plane.x * cameraX;
	ray->rayDir.y = game->player.dir.y + game->player.plane.y * cameraX;
	ray->mapX = (int)game->player.pos.x;
	ray->mapY = (int)game->player.pos.y;
	ray->deltaDist.x = fabs(1.0 / ray->rayDir.x);
	ray->deltaDist.y = fabs(1.0 / ray->rayDir.y);
	ray->hit = 0;
}

/*
** Initializes the DDA parameters for the ray.
** It computes the step direction and initial side distances.
*/
void	init_dda_ray(t_game *game, t_ray *ray)
{
	if (ray->rayDir.x < 0)
	{
		ray->stepX = -1;
		ray->sideDist.x = (game->player.pos.x - ray->mapX) * ray->deltaDist.x;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDist.x = (ray->mapX + 1.0 - game->player.pos.x) * ray->deltaDist.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->stepY = -1;
		ray->sideDist.y = (game->player.pos.y - ray->mapY) * ray->deltaDist.y;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDist.y = (ray->mapY + 1.0 - game->player.pos.y) * ray->deltaDist.y;
	}
}

/*
** Performs the DDA loop until a wall is hit.
*/
void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->map->matrix[ray->mapY][ray->mapX] == 1)
			ray->hit = 1;
	}
}

/*
** Calculates additional properties for the ray after DDA:
** perpendicular wall distance, line height, draw start/end, and initial texture mapping.
** We assume all wall textures share the same dimensions, e.g.:
**   int texWidth  = game->txt.no.width;
**   int texHeight = game->txt.no.height;
*/
void	calculate_ray_properties(t_game *game, t_ray *ray)
{
	int texWidth  = game->txt.no.width;   // or whichever texture
	int texHeight = game->txt.no.height;  // or whichever texture

	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - game->player.pos.x
				+ (1 - ray->stepX) / 2.0) / ray->rayDir.x;
	else
		ray->perpWallDist = (ray->mapY - game->player.pos.y
				+ (1 - ray->stepY) / 2.0) / ray->rayDir.y;

	ray->lineHeight = (int)((double)WIN_H / ray->perpWallDist);

	ray->drawStart = -ray->lineHeight / 2 + WIN_H / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + WIN_H / 2;
	if (ray->drawEnd >= WIN_H)
		ray->drawEnd = WIN_H - 1;

	// Calculate where exactly the wall was hit (for texture X coordinate).
	if (ray->side == 0)
		ray->wallX = game->player.pos.y + ray->perpWallDist * ray->rayDir.y;
	else
		ray->wallX = game->player.pos.x + ray->perpWallDist * ray->rayDir.x;
	ray->wallX -= floor(ray->wallX);

	// Initial texX depends on side & direction
	ray->texX = (int)(ray->wallX * (double)texWidth);
	if (ray->side == 0 && ray->rayDir.x > 0)
		ray->texX = texWidth - ray->texX - 1;
	if (ray->side == 1 && ray->rayDir.y < 0)
		ray->texX = texWidth - ray->texX - 1;

	// Calculate vertical step for each pixel and the initial texture position
	ray->step = (double)texHeight / ray->lineHeight;
	ray->texPos = (ray->drawStart - WIN_H / 2 + ray->lineHeight / 2) * ray->step;
}

/*
** Draws a vertical column (using wall texture) at screen column x.
** We pick which texture to use based on ray->side and ray->rayDir.
*/
void	draw_vertical_column(t_game *game, t_ray *ray, int x)
{
	t_texture *tex;

	// Pick the correct texture:
	if (ray->side == 0)
	{
		if (ray->rayDir.x > 0)
			tex = &game->txt.ea;
		else
			tex = &game->txt.we;
	}
	else
	{
		if (ray->rayDir.y > 0)
			tex = &game->txt.so;
		else
			tex = &game->txt.no;
	}

	// Draw the wall slice from drawStart to drawEnd
	int y = ray->drawStart;
	while (y <= ray->drawEnd)
	{
		// Use the texture's actual height here
		int texY = (int)ray->texPos & (tex->height - 1);
		ray->texPos += ray->step;

		int color = get_tex_color(tex, ray->texX, texY);
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
		&game->img.bpp, &game->img.line_len, &game->img.endian);

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
