/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:55:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 22:34:48 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** put_pixel:
** Writes 'color' into the image's buffer at pixel (x, y). We first check if
** (x, y) lies within the screen bounds (WIN_W x WIN_H). If valid, we compute
** the correct byte in 'img->addr' by offsetting line_size and bpp. Then we
** store our 32-bit color as an unsigned int at that location.
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

	// Check if the color is fully black (MiniLibX treats None as black)
	if ((color & 0x00FFFFFF) == 0x000000)
		return (42); // Return a special value for transparency

	return (color);
}

/*
** init_ray:
** Sets up the ray for a given screen column 'x'. We project 'x' into a
** range [-1,1], stored in camera_x. The ray direction is found by adding
** the camera plane contribution (plane.x * camera_x, etc.) to the player's
** facing direction. The map position is the integer cast of the player's
** (pos.x, pos.y). delta_dist is the absolute distance needed to reach the
** next x or y side in the grid from one side to the next.
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
