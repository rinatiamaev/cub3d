/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caluclate_ray_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:08:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/24 12:11:42 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** calculate_perpendicular_distance:
**
** Once the ray has collided with a wall, we need to calculate the correct
** distance from the player's position to the wall. Since the raw ray length 
** introduces a "fish-eye" effect (distorted perspective), we correct it
** using the perpendicular distance to the wall.
**
** How It Works:
** - If the ray hit a vertical wall (`ray->side == 0`), we compute distance 
**   along the X-direction using `ray->dir.x`.
** - If the ray hit a horizontal wall (`ray->side == 1`), we compute distance 
**   along the Y-direction using `ray->dir.y`.
**
** Usage:
** - This corrected distance is used to calculate wall height (closer = taller).
*/
static void	calculate_perpendicular_distance(t_game *game, t_ray *ray)
{
    if (ray->side == 0) // Ray hit a vertical wall (X-side)
        ray->perp_w_dist = (ray->map.x - game->player.pos.x
				+ (1 - ray->step_dir.x) / 2.0) / ray->dir.x;
    else // Ray hit a horizontal wall (Y-side)
        ray->perp_w_dist = (ray->map.y - game->player.pos.y
				+ (1 - ray->step_dir.y) / 2.0) / ray->dir.y;
}

/*
** calculate_wall_projection:
**
** Determines how tall the wall should appear on the screen (`line_height`)
** and where it should be drawn (`draw_start` to `draw_end`).
**
** How It Works:
** - Wall height is inversely proportional to distance (`perp_w_dist`).
** - Closer walls appear larger, farther walls appear smaller.
** - We center the wall vertically on the screen.
** - If the top (`draw_start`) or bottom (`draw_end`) is out of screen bounds, 
**   we clamp them to avoid overdraw.
**
** Usage:
** - This function determines the wall slice dimensions before texturing.
*/
static	void	calculate_wall_projection(t_ray *ray)
{
    // Compute wall height: Closer walls appear taller, distant walls shorter.
    ray->line_height = (int)((double)WIN_H / ray->perp_w_dist);

    // Compute starting y-coordinate for wall slice (centered vertically).
    ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
    if (ray->draw_start < 0) // Prevent drawing above screen
        ray->draw_start = 0;

    // Compute ending y-coordinate for wall slice.
    ray->draw_end = ray->line_height / 2 + WIN_H / 2;
    if (ray->draw_end >= WIN_H) // Prevent drawing below screen
        ray->draw_end = WIN_H - 1;
}

/*
** calculate_texture_mapping:
**
** Once we know how tall the wall slice is, we determine which part of 
** the wall texture** to use. This ensures proper texturing.
**
** How It Works:
** 1. Compute exact X-coordinate of the wall hit (`wall_x`).
** 2. Convert `wall_x` into a texture coordinate (`tex.x`).
** 3. Compute `step` to determine how many texture pixels per screen pixel.
** 4. Compute `tex_pos`, the initial texture sampling position.
**
** Usage:
** - This function maps world space to texture space, allowing realistic texturing.
*/
static void	calculate_texture_mapping(t_game *game, t_ray *ray)
{
    /*
    ** Step 1: Determine where the wall was hit exactly.
    ** - If we hit a vertical wall (`side == 0`), use the Y-position of the ray.
    ** - If we hit a horizontal wall (`side == 1`), use the X-position.
    */
    if (ray->side == 0) 
        ray->wall_x = game->player.pos.y + ray->perp_w_dist * ray->dir.y;
    else
        ray->wall_x = game->player.pos.x + ray->perp_w_dist * ray->dir.x;

    ray->wall_x -= floor(ray->wall_x); // Keep only the decimal part (0.0 - 1.0)

    /*
    ** Step 2: Convert `wall_x` to a texture X-coordinate (`tex.x`).
    ** - Multiply by texture width (`TEX_W`) to get pixel index.
    ** - If the wall was hit from the right or bottom, we flip the texture.
    */
    ray->tex.x = (int)(ray->wall_x * (double)TEX_W);
    if (ray->side == 0 && ray->dir.x > 0) // Flip texture if ray came from the right
        ray->tex.x = TEX_W - ray->tex.x - 1;
    if (ray->side == 1 && ray->dir.y < 0) // Flip texture if ray came from below
        ray->tex.x = TEX_W - ray->tex.x - 1;

    /*
    ** Step 3: Compute vertical texture stepping (`step`).
    ** - Determines how many texture pixels correspond to one screen pixel.
    ** - A taller wall slice will sample more texture pixels.
    */
    ray->step = (double)TEX_H / ray->line_height;

    /*
    ** Step 4: Compute initial texture position (`tex_pos`).
    ** - This tells us where to start sampling from the texture.
    ** - If the wall slice starts above the screen, we adjust `tex_pos` accordingly.
    */
    ray->tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * ray->step;
}

/*
** calculate_ray_properties:
**
** This function bundles all ray calculations into a single call.
** It computes:
** 1️. Corrected perpendicular distance (`perp_w_dist`) to avoid fish-eye distortion.
** 2️. Wall slice projection (`line_height`, `draw_start`, `draw_end`) to scale walls properly.
** 3️. Texture mapping (`wall_x`, `tex.x`, `tex_pos`) for realistic textures.
**
** Usage:
** - This function is called after raycasting and before rendering.
** - It ensures walls are displayed at the correct height and textured properly.
*/
void	calculate_ray_properties(t_game *game, t_ray *ray)
{
    calculate_perpendicular_distance(game, ray); // Corrects distance for perspective
    calculate_wall_projection(ray);             // Determines wall slice size
    calculate_texture_mapping(game, ray);       // Ensures correct texture mapping
}
