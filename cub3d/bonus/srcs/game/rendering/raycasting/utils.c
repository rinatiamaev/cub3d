/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:55:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/25 10:06:43 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** put_pixel:
** Writes the specified 'color' into the image's pixel buffer at coordinates (x, y).
** The function first checks whether the (x, y) coordinates are within the valid bounds
** of the screen (defined by WIN_W and WIN_H). If they are, it calculates the correct memory
** offset within the image's buffer where this pixel's data is stored and writes the 32-bit
** color value there.
*/
void put_pixel(t_img *img, int x, int y, int color)
{
	char *dst;

	// Check if the coordinates (x, y) are within the bounds of the window.
	// If x or y is out of bounds, exit the function early.
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;

	// Calculate the memory address for the pixel at (x, y):
	// 1. Multiply y by img->line_size to move to the correct row.
	// 2. Multiply x by (img->bpp / 8) to move to the correct column within the row.
	// The sum of these two gives the offset from the start of the image's buffer.
	dst = img->addr + ((y * img->line_size) + (x * (img->bpp / 8)));

	// Write the color value into the calculated memory address.
	// Cast the pointer to unsigned int* because we are writing a 32-bit color value.
	*(unsigned int *)dst = color;
}

/*
** get_tex_color:
**
** This function retrieves the color of a pixel from a texture at the specified
** coordinates (`x, y`). It directly accesses the texture's memory buffer (`tex->addr`)
** without calling `mlx_get_data_addr`, making it faster.
**
** How It Works:
** 1️. Computes the memory address (`pixel`) of the requested pixel.
** 2. Reads the color value from that memory address.
** 3. Checks if the color is fully black (`#000000`), and if so, returns `42` as a transparency indicator.
**
** Usage:
** - Used for texture mapping in raycasting to retrieve wall, floor, ceiling, or sprite colors.
** - Works efficiently by directly computing the pixel position in memory.
*/
int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*pixel;
	int		color;

	/*
	** Step 1: Compute the pixel's memory address.
	** - `tex->addr` is the **starting address** of the texture data.
	** - Each row (y) has `tex->line_size` bytes.
	** - Each pixel (x) takes `tex->bpp / 8` bytes.
	**
	** The formula calculates the **exact byte offset** in the texture buffer.
	*/
	pixel = tex->addr + (y * tex->line_size + x * (tex->bpp / 8));

	/*
	** Step 2: Read the color from memory.
	** - The memory at `pixel` is cast to an `unsigned int *`, so we read a full **32-bit color value**.
	*/
	color = *(unsigned int *)pixel;

	/*
	** Step 3: Check for transparency.
	** - If the color is exactly **black (0x000000)**, return `42` instead, as a transparency key.
	*/
	if ((color & 0x00FFFFFF) == 0x000000) // Ignore alpha, check only RGB
		return (42); // Transparency indicator

	return (color); // Return the actual texture color
}


/*
** init_ray:
**
** This function initializes a `t_ray` structure for a specific vertical screen column `x`.
** Each column represents a single ray cast from the player's viewpoint to determine
** what is visible at that screen position.
**
** The function:
** 1. Projects the screen column (`x`) onto a normalized coordinate (`camera_x`).
** 2. Calculates the direction of the ray in the game world.
** 3️. Determines the starting position of the ray in the grid (integer map coordinates).
** 4️. Computes `delta_dist.x` and `delta_dist.y` to determine how far the ray travels
**    before hitting a grid boundary in the x and y directions.
** 5️. Initializes `ray->hit` to `false`, meaning the ray has not hit a wall yet.
**
** This function is called at the start of each column's raycasting process.
*/
void init_ray(t_game *game, t_ray *ray, int x)
{
	/*
	** Step 1: Normalize the screen column 'x' to `camera_x`, a range from -1 to 1.
	** - The center column (middle of the screen) corresponds to `camera_x = 0`.
	** - The leftmost column corresponds to `camera_x = -1`.
	** - The rightmost column corresponds to `camera_x = 1`.
	**
	** This value determines how far left or right the ray is cast relative to the player's view.
	*/
	double camera_x = 2.0 * (double)x / (double)WIN_W - 1.0;

	/*
	** Step 2: Calculate the direction of the ray in the game world.
	** - The player's direction vector (`dir.x`, `dir.y`) represents where they are facing.
	** - The camera plane vector (`plane.x`, `plane.y`) determines the field of view.
	** - Multiplying `plane` by `camera_x` shifts the ray's direction based on its screen position.
	**
	** This gives each column its unique ray direction.
	*/
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;

	/*
	** Step 3: Determine the grid cell (map position) where the ray starts.
	** - The player's exact position (`pos.x`, `pos.y`) is stored as floating-point values.
	** - Casting them to `int` gives the **grid cell coordinates (`map.x`, `map.y`).
	** - This tells us which tile in the map the player is standing on when casting the ray.
	*/
	ray->map.x = (int)game->player.pos.x;
	ray->map.y = (int)game->player.pos.y;

	/*
	** Step 4: Compute `delta_dist.x` and `delta_dist.y`.
	** - These values represent how far the ray must travel in the x or y direction
	**   to cross the next grid line.
	** - They are calculated as the absolute inverse of the ray direction components.
	** - The reason we take `fabs(1.0 / dir.x)` instead of just `1.0 / dir.x`:
	**   - If the ray is moving left, `dir.x` is negative, so we take `fabs` to ensure it's positive.
	**   - If the ray is moving right, `dir.x` is positive, so the result remains positive.
	** - The same applies for the y-direction.
	**
	** This ensures that we can correctly determine which direction the ray will step first.
	*/
	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	ray->delta_dist.y = fabs(1.0 / ray->dir.y);

	/*
	** Step 5: Initialize the ray hit status.
	** - `ray->hit = false` means the ray has not yet hit a wall.
	** - This will be updated in the DDA loop once the ray collides with a wall.
	*/
	ray->hit = false;
}


/*
** init_dda_ray:
**
** This function initializes the step direction (`step_dir.x`, `step_dir.y`) 
** and the initial `side_dist` values needed for the DDA (Digital Differential 
** Analysis) algorithm used in raycasting.
**
** The DDA algorithm works by moving step by step through a grid-based map
** (like a tile map), following a ray from the player's position until a 
** wall is hit. It determines whether the ray should step in the x-direction 
** or the y-direction first, based on the player's position and the ray’s 
** direction.
**
** 1. Determines the step direction (`step_dir.x`, `step_dir.y`):
**     - If `ray->dir.x < 0`, the ray is moving left (-1 step in x).
**     - If `ray->dir.x >= 0`, the ray is moving right (+1 step in x).
**     - If `ray->dir.y < 0`, the ray is moving up (-1 step in y).
**     - If `ray->dir.y >= 0`, the ray is moving down (+1 step in y).
**
** 2️. Computes the initial `side_dist.x` and `side_dist.y`:
**     - These distances determine how far the ray needs to travel
**       before hitting the first vertical or horizontal grid boundary.
**
** Usage:
** - This function is called before the DDA loop in raycasting.
** - The computed values are used to determine which grid line (x or y) 
**   is hit first in the `perform_dda()` function.
*/
void	init_dda_ray(t_game *game, t_ray *ray)
{
	// Determine the step direction in the X-axis
	if (ray->dir.x < 0)
	{
		ray->step_dir.x = -1; // Move left in the grid
		ray->side_dist.x = (game->player.pos.x - ray->map.x) * ray->delta_dist.x;
		/*
		** Calculation Breakdown:
		** - `game->player.pos.x` is the player's exact position in world space.
		** - `ray->map.x` is the integer grid coordinate where the player is.
		** - `(game->player.pos.x - ray->map.x)` calculates the distance from the 
		**   player’s position to the left side of the current tile.
		** - `ray->delta_dist.x` is the unit step distance needed to cross one 
		**   tile in the x-direction (already computed before calling this function).
		*/
	}
	else
	{
		ray->step_dir.x = 1; // Move right in the grid
		ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x) * ray->delta_dist.x;
		/*
		** Calculation Breakdown:
		** - `(ray->map.x + 1.0)` represents the right edge of the current tile.
		** - `(ray->map.x + 1.0 - game->player.pos.x)` computes the distance 
		**   from the player’s position to the right side of the tile.
		** - Multiplying by `ray->delta_dist.x` converts this to the correct unit.
		*/
	}

	// Determine the step direction in the Y-axis
	if (ray->dir.y < 0)
	{
		ray->step_dir.y = -1; // Move up in the grid
		ray->side_dist.y = (game->player.pos.y - ray->map.y) * ray->delta_dist.y;
		/*
		** Calculation Breakdown:
		** - Similar to X, but in the Y-direction.
		** - Computes how far the player is from the top side of the current tile.
		** - `ray->delta_dist.y` is the step size for moving through tiles in Y.
		*/
	}
	else
	{
		ray->step_dir.y = 1; // Move down in the grid
		ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y) * ray->delta_dist.y;
		/*
		** - Computes how far the player is from the bottom side of the current tile.
		** - Converts this to the correct unit using `ray->delta_dist.y`.
		*/
	}
}

