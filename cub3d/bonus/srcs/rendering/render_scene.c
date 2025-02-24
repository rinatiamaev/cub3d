/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/24 09:34:22 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
** This function fills the entire image with two colors: one for the ceiling (top half)
** and one for the floor (bottom half). The image is divided horizontally into two halves.
** The ceiling color is applied to all pixels in the rows from 0 up to (but not including)
** WIN_H/2, while the floor color is applied from WIN_H/2 to WIN_H-1.
**
** Detailed Process:
** 1. The outer loop iterates over each row (y-coordinate) of the image.
** 2. For each row, an inner loop iterates over every pixel in that row (x-coordinate).
** 3. For rows in the top half, the put_pixel function is called with the ceiling_color.
** 4. For rows in the bottom half, the put_pixel function is called with the floor_color.
*/
static void fill_ceiling_and_floor(t_img *img, int ceiling_color, int floor_color)
{
    int x;  // Horizontal coordinate for iterating over each pixel in a row.
    int y;  // Vertical coordinate for iterating over each row in the image.

    y = 0;
    // Loop over the top half of the image rows for the ceiling.
    while (y < WIN_H / 2)
    {
        x = 0;
        // For the current row, iterate through each column (pixel) from 0 to WIN_W-1.
        while (x < WIN_W)
        {
            // Set the pixel at (x, y) to the ceiling_color.
            put_pixel(img, x, y, ceiling_color);
            x++;  // Move to the next pixel in the row.
        }
        y++;  // Move to the next row.
    }
    // Loop over the bottom half of the image rows for the floor.
    while (y < WIN_H)
    {
        x = 0;
        // For the current row, iterate through each column (pixel) from 0 to WIN_W-1.
        while (x < WIN_W)
        {
            // Set the pixel at (x, y) to the floor_color.
            put_pixel(img, x, y, floor_color);
            x++;  // Move to the next pixel in the row.
        }
        y++;  // Move to the next row.
    }
}


void	render_scene(t_game *game)
{
	t_ray	ray;		// Declare a ray structure to hold all information for the current ray.
	int		x;			// Variable to iterate over each vertical screen column.
	
	// Allocate a z-buffer array to store the perpendicular distance for each column.
    // This will be used later for depth calculations (e.g., drawing sprites or NPCs).
	double	*z_buffer = x_calloc(game, WIN_W, sizeof(double));

	// Create a new image with width WIN_W and height WIN_H.
    // This image will be drawn onto the window later.
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);

	// Retrieve the memory address of the image's pixel data.
    // Also get additional parameters: bits per pixel, line size, and endian information.
	game->img.addr = mlx_get_data_addr(game->img.ptr,
										&game->img.bpp,
										&game->img.line_size,
										&game->img.endian);

	// Fill the image with ceiling and floor colors.
    // This sets the background for the upper (ceiling) and lower (floor) parts of the scene.
	fill_ceiling_and_floor(&game->img,
							game->map->conf.ceiling_color,
							game->map->conf.floor_color);
	x = 0;
	// Loop through every vertical column (x-coordinate) on the screen.
	while (x < WIN_W)
	{
		// Initialize the ray for this column based on the player's position and view.
		init_ray(game, &ray, x);

		// Set up initial variables for the DDA (Digital Differential Analysis) algorithm.
        // This prepares the ray for stepping through the grid.
		init_dda_ray(game, &ray);

		// Execute the DDA algorithm to step through the grid cell by cell until a wall is hit.
		// This calculates the perpendicular distance to the wall and other properties of the ray.
		perform_dda(game, &ray);

		// After hitting a wall, calculate properties of the ray such as the perpendicular
        // distance to the wall, the exact hit location, and texture coordinates.
		calculate_ray_properties(game, &ray);

		// Use the calculated ray properties to draw a vertical slice of the wall on the screen.
		draw_wall_column(game, &ray, x);

		// Save the perpendicular distance to the wall in the z-buffer for later use.
		z_buffer[x] = ray.perp_w_dist;
		x++;
	}

	// After processing all wall columns, draw any NPCs (or sprites) in the scene.
    // The z-buffer is used to correctly handle depth, ensuring NPCs appear in front or behind walls as needed.
	draw_npc(game, game->witch_kitty, z_buffer);
	draw_minimap(game);

	// Render the final image to the window.
	mlx_put_image_to_window(game->mlx, game->window->ptr, game->img.ptr, 0, 0);

	// Destroy the image to free up resources, since it has been rendered to the window.
	mlx_destroy_image(game->mlx, game->img.ptr);
	// Free the memory allocated for the z-buffer.
	free(z_buffer);
}
