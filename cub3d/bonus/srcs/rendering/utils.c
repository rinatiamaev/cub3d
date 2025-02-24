/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:55:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/22 22:50:56 by nlouis           ###   ########.fr       */
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
** Retrieves the pixel color from the texture at (x, y). We assume x,y are
** within the texture's size. This function does not call mlx_get_data_addr;
** we directly compute the pixel offset in 'tex->addr'.
*/
int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = tex->addr + (y * tex->line_size + x * (tex->bpp / 8));
	color = *(unsigned int *)pixel;
	if ((color & 0x00FFFFFF) == 0x000000)
		return (42);
	return (color);
}

/*
** init_ray:
** This function initializes a ray structure for a specific vertical screen column 'x'.
** It projects 'x' onto a normalized camera space coordinate (camera_x) ranging from -1 to 1,
** which represents the relative horizontal position on the screen.
**
** The ray's direction is computed by adding the player's facing direction and the scaled
** camera plane vector (which determines the field of view) multiplied by camera_x.
**
** The current grid cell in the map (map.x and map.y) is set to the integer part of the
** player's position. This helps determine where the ray starts in the grid.
**
** Finally, delta_dist.x and delta_dist.y are calculated. These represent the distance the ray
** must travel in the x and y direction, respectively, to go from one side of a grid cell to the next.
** They are computed as the absolute inverse of the ray's direction components.
** The ray->hit flag is also initialized to false, indicating that the ray has not yet hit a wall.
*/
void init_ray(t_game *game, t_ray *ray, int x)
{
    // Map the current screen column 'x' to a normalized coordinate between -1 and 1.
    // This determines how far left or right the column is relative to the center of the view.
    double camera_x = 2.0 * (double)x / (double)WIN_W - 1.0;

    // Calculate the ray direction by combining the player's direction with the camera plane offset.
    // The player's direction vector (game->player.dir) indicates where the player is facing.
    // The camera plane vector (game->player.plane) defines the 2D plane perpendicular to the player's view.
    // Multiplying the camera plane vector by camera_x scales it to the current column's relative position.
    ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
    ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;

    // Set the starting grid coordinates for the ray to the player's current grid position.
    // Casting the player's position to an integer gives the map cell in which the player resides.
    ray->map.x = (int)game->player.pos.x;
    ray->map.y = (int)game->player.pos.y;

    // Compute the distance the ray must travel to move from one x-side or y-side of a grid cell to the next.
    // This is calculated as the absolute value of the inverse of the ray's direction components.
    // It helps determine how far the ray has to travel in each axis to cross a grid line.
    ray->delta_dist.x = fabs(1.0 / ray->dir.x);
    ray->delta_dist.y = fabs(1.0 / ray->dir.y);

    // Initialize the hit flag to false; it will be set to true when the ray eventually hits a wall.
    ray->hit = false;
}

/*
** init_dda_ray:
** Prepares step_dir (sign of movement in x and y) and computes side_dist,
** which is the distance to the first x-side or y-side from the player's
** position. If dir.x < 0, step_dir.x is -1, meaning we'll move left in
** the map. side_dist.x is then the distance from the player's x pos
** to the left side of the tile. Similarly for dir.y.
*/
void	init_dda_ray(t_game *game, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_dir.x = -1;
		ray->side_dist.x
			= (game->player.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_dir.x = 1;
		ray->side_dist.x
			= (ray->map.x + 1.0 - game->player.pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_dir.y = -1;
		ray->side_dist.y
			= (game->player.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_dir.y = 1;
		ray->side_dist.y
			= (ray->map.y + 1.0 - game->player.pos.y) * ray->delta_dist.y;
	}
}
