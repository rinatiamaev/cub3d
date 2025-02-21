/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caluclate_ray_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:54:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 20:55:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
