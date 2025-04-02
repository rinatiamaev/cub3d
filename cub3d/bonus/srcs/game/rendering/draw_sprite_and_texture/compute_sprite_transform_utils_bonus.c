/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_sprite_transform_utils_bonus.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:18:36 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 14:57:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Computes the determinant of the 2D camera transformation matrix.
 *
 * This value represents the determinant of the matrix used to project
 * world-space positions (relative to the player) into camera space.
 * 
 * A non-zero determinant is required to safely compute the inverse matrix,
 * which is used during sprite rendering to get screen coordinates.
 *
 * Formula:
 *     det = view_plane.x * dir.y - dir.x * view_plane.y
 *
 * @param player The player structure (provides direction and camera plane).
 * @return The determinant value for the player's camera matrix.
 */
double	compute_determinant(t_player player)
{
	return (player.view_plane.x * player.facing_dir.y
		- player.facing_dir.x * player.view_plane.y);
}

/**
 * @brief Computes the inverse of the camera matrix determinant.
 *
 * This function returns the reciprocal of the determinant used in the
 * sprite projection matrix. It is used to transform a sprite's relative
 * position into camera space.
 *
 * @param det The determinant of the camera transformation matrix.
 * @return The inverse of the determinant (1.0 / det).
 */
double	compute_inverse_determinant(double det)
{
	return (1.0 / det);
}

/**
 * @brief Computes the X coordinate of the sprite in camera space.
 *
 * This function transforms the sprite's relative position into the player's
 * camera space, using the inverse of the determinant and the player's
 * facing direction. The result is the horizontal position of the sprite
 * relative to the camera plane.
 *
 * Formula:
 *     transform.x = inv_det * (dir.y * rel.x - dir.x * rel.y)
 *
 * @param player The player structure (provides direction vector).
 * @param rel The relative position of the sprite to the player.
 * @param inv_det The inverse determinant of the camera matrix.
 * @return The X coordinate of the sprite in camera space.
 */
double	compute_transform_x(t_player player, t_dpoint rel, double inv_det)
{
	return (inv_det * (player.facing_dir.y * rel.x
			- player.facing_dir.x * rel.y));
}

/**
 * @brief Computes the Y coordinate of the sprite in camera space.
 *
 * This function transforms the sprite's relative position into the player's
 * camera space using the inverse determinant and the player's camera plane
 * (perpendicular to the direction vector). The result is the depth of the
 * sprite relative to the camera — it must be positive to be visible.
 *
 * Formula:
 *     transform.y = inv_det * (-plane.y * rel.x + plane.x * rel.y)
 *
 * @param player The player structure (provides view plane vector).
 * @param rel The relative position of the sprite to the player.
 * @param inv_det The inverse determinant of the camera matrix.
 * @return The Y coordinate (depth) of the sprite in camera space.
 */
double	compute_transform_y(t_player player, t_dpoint rel, double inv_det)
{
	return (inv_det * (-player.view_plane.y * rel.x
			+ player.view_plane.x * rel.y));
}

/**
 * @brief Checks if the sprite is in front of the player (visible).
 *
 * This function determines whether the sprite lies in front of the player
 * in camera space. A positive Y value means the sprite is in front of the
 * camera; negative or near-zero values indicate it's behind or too close
 * to the player to render correctly.
 *
 * @param transform_y The Y coordinate (depth) of the sprite in camera space.
 * @return true if the sprite is in front of the player, false otherwise.
 */
bool	is_sprite_in_front(double transform_y)
{
	return (transform_y > 0.001);
}
