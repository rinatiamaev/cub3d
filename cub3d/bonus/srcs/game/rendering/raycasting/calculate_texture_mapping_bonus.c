/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_texture_mapping_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:52:46 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 14:42:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Computes the exact wall hit position on the texture axis.
 *
 * This function calculates the exact point on the wall (in world space)
 * where the ray hit. Depending on whether the ray hit a vertical (X-axis)
 * or horizontal (Y-axis) wall, the function uses the perpendicular wall
 * distance and the ray direction to compute the position along the wall.
 *
 * The result is later used to extract the fractional part of the wall
 * coordinate, which determines the horizontal offset for texture sampling.
 *
 * @param game Pointer to the game state (used to access player position).
 * @param ray Pointer to the ray structure containing hit information.
 * @return The exact world position of the wall hit along the texture axis.
 */
static double	get_exact_wall_position(t_game *game, t_ray *ray)
{
	double	offset;
	double	wall_position;

	if (ray->side == 0)
	{
		offset = ray->perp_w_dist * ray->dir.y;
		wall_position = game->player.pos.y + offset;
	}
	else
	{
		offset = ray->perp_w_dist * ray->dir.x;
		wall_position = game->player.pos.x + offset;
	}
	return (wall_position);
}

/**
 * @brief Adjusts the wall hit position for animated door offsets.
 *
 * If the ray hit a door (`ray->hit == 2`), this function retrieves the door
 * at the ray's current map cell and adds its opening offset to the horizontal
 * wall hit position (`wall_x`). This allows the texture mapping to visually
 * reflect how far the door is open.
 *
 * The result is wrapped to stay within the [0.0, 1.0) range using a modulo
 * helper, ensuring consistent texture sampling.
 *
 * @param game Pointer to the game state (used to find door data).
 * @param ray Pointer to the ray that hit a door.
 * @param wall_x Initial fractional hit position on the wall.
 * @return Adjusted wall hit position including door offset.
 */
static double	adjust_for_door_offset(t_game *game, t_ray *ray, double wall_x)
{
	t_door	*door;

	if (ray->hit == 2)
	{
		door = find_door_at(game, ray->map);
		if (door)
		{
			wall_x += door->offset;
			wall_x = wrap_in_range(wall_x, 1.0);
		}
	}
	return (wall_x);
}

/**
 * @brief Flips the texture X coordinate for correct orientation.
 *
 * Depending on the side of the wall that was hit and the ray's direction,
 * the wall texture might need to be flipped horizontally to appear correctly.
 *
 * This function adjusts `tex_x` so that textures are not mirrored incorrectly
 * when the ray hits certain sides (e.g. west vs. east walls, or
 * north vs. south).
 *
 * @param ray Pointer to the ray that hit the wall.
 * @param tex_x Initial texture X coordinate.
 * @return Corrected (possibly flipped) texture X coordinate.
 */
static inline int	flip_texture_x_if_needed(t_ray *ray, int tex_x)
{
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = TEX_W - tex_x - 1;
	return (tex_x);
}

/**
 * @brief Computes texture sampling parameters for wall rendering.
 *
 * This function prepares the ray with all texture-related information needed
 * to draw a vertical wall column. It performs the following steps:
 *
 * 1. Computes the exact world position where the ray hit the wall.
 * 2. Extracts the fractional component of the hit position to determine
 *    the horizontal offset within the wall texture.
 * 3. Adjusts this offset if the hit was on a door, to reflect its animation.
 * 4. Converts the fractional offset into a pixel coordinate on the texture.
 * 5. Flips the texture X coordinate if needed, based on the wall side and
 *    ray direction, to ensure correct orientation.
 * 6. Calculates how much to advance in the texture vertically per screen pixel
 *    (`step`) and initializes the starting texture position (`tex_pos`).
 *
 * These values are then used in the wall rendering function to sample the
 * correct portion of the wall texture.
 *
 * @param game Pointer to the game state (used for player and door data).
 * @param ray Pointer to the ray to be populated with texture mapping info.
 */
void	calculate_texture_mapping(t_game *game, t_ray *ray)
{
	double	exact_pos;
	double	wall_fraction;

	exact_pos = get_exact_wall_position(game, ray);
	wall_fraction = get_fractional_part(exact_pos);
	ray->wall_x = adjust_for_door_offset(game, ray, wall_fraction);
	ray->tex.x = (int)(ray->wall_x * (double)TEX_W);
	ray->tex.x = flip_texture_x_if_needed(ray, ray->tex.x);
	ray->step = (double)TEX_H / ray->line_height;
	ray->tex_pos
		= (ray->draw_start - (WIN_H >> 1) + (ray->line_height / 2)) * ray->step;
}
