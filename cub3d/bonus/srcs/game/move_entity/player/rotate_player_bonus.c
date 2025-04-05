/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:18 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:14:31 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Rotates the player's view direction and updates the view plane.
 *
 * This function updates the player's facing direction and camera view plane
 * after applying a rotation by the given angle. It uses trigonometric 
 * functions to compute the new direction and plane vectors.
 *
 * @details
 * - `facing_angle` stores the angle (in radians) the player is facing.
 * - `wrap_angle` ensures the angle remains within the valid 0 to 2π range.
 * - `facing_dir` is a normalized vector (x = cos(angle), y = sin(angle))
 *   that represents the player's direction.
 * - `view_plane` is perpendicular to `facing_dir`, scaled by FOV. It is 
 *   used in the raycasting algorithm to determine the visible field.
 *
 * @param player Pointer to the player structure.
 * @param angle_delta Angle to rotate (in radians). Positive is clockwise.
 */
static void	rotate_player(t_player *player, double angle_delta)
{
	player->facing_angle = wrap_angle(player->facing_angle + angle_delta);
	player->facing_dir.x = cos(player->facing_angle);
	player->facing_dir.y = sin(player->facing_angle);
	player->view_plane.x = -sin(player->facing_angle) * FOV;
	player->view_plane.y = cos(player->facing_angle) * FOV;
}

/**
 * @brief Rotates the player to the left by a specified angle.
 *
 * This function rotates the player's view direction to the left
 * (counter-clockwise) by the player's rotation speed multiplied
 * by the elapsed time.
 *
 * @param player Pointer to the player structure.
 * @param delta_time Time elapsed since last frame.
 */
void	rotate_player_left(t_player *player, double delta_time)
{
	double	angle_delta;

	angle_delta = player->rot_speed * delta_time;
	rotate_player(player, angle_delta);
}

/**
 * @brief Rotates the player to the right by a specified angle.
 *
 * This function rotates the player's view direction to the right
 * (clockwise) by the player's rotation speed multiplied
 * by the elapsed time.
 *
 * @param player Pointer to the player structure.
 * @param delta_time Time elapsed since last frame.
 */
void	rotate_player_right(t_player *player, double delta_time)
{
	double	angle_delta;

	angle_delta = -player->rot_speed * delta_time;
	rotate_player(player, angle_delta);
}
