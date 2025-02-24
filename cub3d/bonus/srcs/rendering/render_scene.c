/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/24 12:17:22 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** perform_dda:
**
** This function traces the ray step by step through a grid-based map
** until it hits a wall. It uses the Digital Differential 
** Analysis (DDA) algorithm, which efficiently determines which grid cell the 
** ray will move to next by comparing distances in the x and y directions.
**
** How It Works:
** 1. Compare `side_dist.x` and `side_dist.y`:
**    - If `side_dist.x < side_dist.y`, the ray crosses a vertical (X-side) wall first.
**    - Otherwise, the ray crosses a horizontal (Y-side) wall first.
**
** 2. Step to the next grid cell:
**    - If moving in X, update `map.x` and `side_dist.x`.
**    - If moving in Y, update `map.y` and `side_dist.y`.
**    - Also, store whether the hit was on an X-side (0) or Y-side (1).
**
** 3. Check if the new grid cell contains a wall:
**    - If `map[y][x] == 1`, a wall is found, so `ray->hit` is set to `1`, stopping the loop.
**
** Usage:
** - This function is called inside the main rendering loop to determine 
**   where the ray stops, allowing textures to be drawn correctly.
** - It ensures that only visible walls are processed, making the rendering efficient.
*/
void perform_dda(t_game *game, t_ray *ray)
{
    /*
    ** Step 1: Keep stepping through the grid until we hit a wall (`ray->hit == 1`).
    */
    while (ray->hit == 0)
    {
        /*
        ** Step 2: Compare `side_dist.x` and `side_dist.y` to determine 
        ** which grid boundary the ray crosses first.
        */
        if (ray->side_dist.x < ray->side_dist.y)
        {
            /*
            ** Step 3a: The ray crosses a vertical boundary (X-side first).
            ** - Move the ray to the next tile in the X direction (`map.x`).
            ** - Increase `side_dist.x` by `delta_dist.x`, since we moved one step in X.
            ** - Mark `ray->side = 0`, indicating an X-side wall was hit.
            */
            ray->side_dist.x += ray->delta_dist.x;
            ray->map.x += ray->step_dir.x;
            ray->side = 0;
        }
        else
        {
            /*
            ** Step 3b: The ray crosses a horizontal boundary (Y-side first).
            ** - Move the ray to the next tile in the Y direction (`map.y`).
            ** - Increase `side_dist.y` by `delta_dist.y`, since we moved one step in Y.
            ** - Mark `ray->side = 1`, indicating a Y-side wall was hit.
            */
            ray->side_dist.y += ray->delta_dist.y;
            ray->map.y += ray->step_dir.y;
            ray->side = 1;
        }

        /*
        ** Step 4: Check if the new tile (`map[x][y]`) contains a wall (`1`).
        ** - If the new position contains a wall, stop the loop (`ray->hit = 1`).
        */
        if (game->map->matrix[ray->map.y][ray->map.x] == 1)
            ray->hit = 1;
    }
}


/*
** select_wall_texture:
**
** This function determines which wall texture should be used 
** based on where the ray hit the wall in the world.
**
** How It Works:
** 1️. Check which axis (X or Y) the wall was hit on.
**    - `ray->side == 0` → Wall hit on an X-side (vertical wall).
**    - `ray->side == 1` → Wall hit on a Y-side (horizontal wall).
**
** 2. Determine the wall's facing direction:
**    - For X-walls:
**      - If `ray->dir.x > 0`, the ray hit an East-facing wall → Use `ea` (east texture).
**      - If `ray->dir.x < 0`, the ray hit a West-facing wall → Use `we` (west texture).
**
**    - For Y-walls:
**      - If `ray->dir.y > 0`, the ray hit a South-facing wall → Use `so` (south texture).
**      - If `ray->dir.y < 0`, the ray hit a North-facing wall → Use `no` (north texture).
**
** Usage:
** - Called in `draw_wall_column` to select the correct texture before drawing the wall.
** - Ensures that each wall has the correct texture based on orientation.
*/
static t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
    /*
    ** Step 1: Determine whether the ray hit a vertical wall (X-side) or a horizontal wall (Y-side).
    ** - `ray->side == 0` → The ray hit a vertical wall (East or West).
    ** - `ray->side == 1` → The ray hit a horizontal wall (North or South).
    */
    if (ray->side == 0) // Vertical wall (East or West)
    {
        /*
        ** Step 2: Check which direction the ray was traveling in.
        ** - If `ray->dir.x > 0`, the ray was moving right, so it hit an East-facing wall.
        ** - If `ray->dir.x < 0`, the ray was moving left, so it hit a West-facing wall.
        */
        if (ray->dir.x > 0)
            return (&game->tex.ea); // East wall texture
        else
            return (&game->tex.we); // West wall texture
    }
    else // Horizontal wall (North or South)
    {
        /*
        ** Step 3: Check which direction the ray was traveling in.
        ** - If `ray->dir.y > 0`, the ray was moving down, so it hit a South-facing wall.
        ** - If `ray->dir.y < 0`, the ray was moving up, so it hit a North-facing wall.
        */
        if (ray->dir.y > 0)
            return (&game->tex.so); // South wall texture
        else
            return (&game->tex.no); // North wall texture
    }
}


/*
** draw_wall_column:
**
** This function renders a single vertical slice of a wall at screen column `x`.
** It determines the correct wall texture, computes the texture coordinates for 
** each pixel row, and draws the textured wall slice onto the screen.
**
** How It Works:
** 1️. Select the correct texture depending on the wall's orientation (N/S/E/W).
** 2️. Loop from `draw_start` to `draw_end`, which represents the visible height of the wall.
** 3. For each pixel row (`y`):
**     - Compute which row in the texture to sample.
**     - Retrieve the pixel color from the texture.
**     - Draw the pixel to the screen using `put_pixel`.
**
** Usage:
** - This function is called once per column in the rendering loop of the raycasting engine.
** - It ensures that each ray is textured correctly based on the ray's hit position.
** - The `ray->tex_pos` and `ray->step` values are precomputed to map the screen pixels to the texture correctly.
*/
void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
    t_texture	*tex;
    int			y;
    int			color;

    /*
    ** Step 1: Select the correct texture for this wall.
    ** - Walls may have different textures depending on the hit direction (N/S/E/W).
    ** - `select_wall_texture` determines the correct texture to use.
    */
    tex = select_wall_texture(game, ray);

    /*
    ** Step 2: Loop through all pixels in the visible wall slice.
    ** - `draw_start`: The topmost pixel of the wall slice.
    ** - `draw_end`: The bottom-most pixel of the wall slice.
    ** - The loop ensures only visible pixels are drawn (avoiding overdraw).
    */
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        /*
        ** Step 3: Compute the Y-coordinate in the texture (`ray->tex.y`).
        ** - `ray->tex_pos` keeps track of which part of the texture we are currently sampling.
        ** - We convert `tex_pos` to an integer to get the corresponding row in the texture.
        ** - The `& (tex->size.y - 1)` ensures we stay within the texture bounds (power-of-2 textures).
        */
        ray->tex.y = (int)ray->tex_pos & (tex->size.y - 1);

        /*
        ** Step 4: Move `ray->tex_pos` downward to the next row.
        ** - `ray->step` determines how much we advance in the texture per screen pixel.
        */
        ray->tex_pos += ray->step;

        /*
        ** Step 5: Get the correct texture color for this pixel.
        ** - We sample the texture at (`ray->tex.x`, `ray->tex.y`).
        */
        color = get_tex_color(tex, ray->tex.x, ray->tex.y);

        /*
        ** Step 6: Draw the pixel to the screen at (`x`, `y`).
        ** - `put_pixel` places the retrieved color at the correct screen location.
        */
        put_pixel(&game->img, x, y, color);

        y++; // Move to the next pixel row
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
