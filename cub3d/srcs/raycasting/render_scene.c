/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 14:06:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
static int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	pixel = tex->addr + (y * tex->line_size + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
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
** calculate_perpendicular_distance:
** After we know which grid cell we collided with, we get the final
** distance. For side=0, perp_w_dist is computed along x, for side=1,
** along y. This corrects the fish-eye effect by using the perpendicular
** distance from the camera plane, not the raw collision distance.
*/
static void	calculate_perpendicular_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_w_dist = (ray->map.x - game->player.pos.x
				+ (1 - ray->step_dir.x) / 2.0) / ray->dir.x;
	else
		ray->perp_w_dist = (ray->map.y - game->player.pos.y
				+ (1 - ray->step_dir.y) / 2.0) / ray->dir.y;
}

/*
** calculate_wall_projection:
** Determines how tall the wall slice should be on screen (line_height)
** and which part of the screen we draw it to (draw_start to draw_end).
** The height is found by dividing WIN_H by perp_w_dist. That makes
** closer walls look taller and distant walls look shorter.
*/
static	void	calculate_wall_projection(t_ray *ray)
{
	ray->line_height = (int)((double)WIN_H / ray->perp_w_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

/*
** calculate_texture_mapping:
** Once we know how tall the wall slice is, we figure out which x coord
** on the wall texture to sample from (wall_x). Then we store tex.x and
** compute tex_pos as the initial position to read from in the texture.
** step is how many texture pixels we move per screen pixel vertically.
*/
static void	calculate_texture_mapping(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos.y + ray->perp_w_dist * ray->dir.y;
	else
		ray->wall_x = game->player.pos.x + ray->perp_w_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.x = (int)(ray->wall_x * (double)TEX_W);
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.x = TEX_W - ray->tex.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.x = TEX_W - ray->tex.x - 1;
	ray->step = (double)TEX_H / ray->line_height;
	ray->tex_pos
		= (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * ray->step;
}

/*
** calculate_ray_properties:
** Bundles the perpendicular distance, wall projection size, and texture
** mapping into one call. We do not handle the actual drawing here.
*/
void	calculate_ray_properties(t_game *game, t_ray *ray)
{
	calculate_perpendicular_distance(game, ray);
	calculate_wall_projection(ray);
	calculate_texture_mapping(game, ray);
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
void	fill_ceiling_and_floor(t_img *img, int ceiling_color, int floor_color)
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
