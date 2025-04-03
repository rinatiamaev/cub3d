/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:59:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:45:43 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if the mouse cursor is inside the game window.
 *
 * Verifies whether the current mouse position is within the dimensions of
 * the specified window. This is used to ensure input is only processed when
 * the cursor is within the visible game area.
 *
 * @param m Pointer to the mouse data structure.
 * @param window Pointer to the window structure.
 * @return true if the mouse is inside the window, false otherwise.
 */
static bool	is_mouse_inside_window(t_mouse_data *m, t_window *window)
{
	return (m->position.x >= 0 && m->position.x < window->size.x
		&& m->position.y >= 0 && m->position.y < window->size.y);
}

/**
 * @brief Updates the player's rotation speed based on mouse movement.
 *
 * Calculates the horizontal distance between the current mouse position and
 * the center of the screen. If this distance exceeds a threshold and the
 * mouse is within the window bounds, the rotation speed is updated based
 * on that distance, the player's rotation speed, and a sensitivity factor.
 * Otherwise, the speed is gradually reduced (simulating inertia).
 *
 * @param m Pointer to the mouse data structure.
 * @param game Pointer to the game structure.
 * @param window Pointer to the window structure.
 */
static void	update_rotation_speed(t_mouse_data *m, t_game *game,
															t_window *window)
{
	m->delta_x = m->position.x - m->center.x;
	if (fabs(m->delta_x) > (window->size.x / 5)
		&& is_mouse_inside_window(m, window))
	{
		m->rotation_speed
			= m->delta_x * m->sensitivity * game->player.rot_speed;
	}
	else
	{
		m->rotation_speed *= 0.9;
		if (fabs(m->rotation_speed) < 0.0001)
			m->rotation_speed = 0.0;
	}
}

/**
 * @brief Applies rotation to the player based on mouse movement.
 *
 * Rotates the player either to the left or right depending on the sign of
 * the rotation speed, which is calculated from mouse horizontal movement.
 *
 * @param m Pointer to the mouse data structure containing rotation speed.
 * @param game Pointer to the game structure containing the player.
 */
static void	apply_rotation(t_mouse_data *m, t_game *game)
{
	if (m->rotation_speed > 0)
		rotate_player_left(&game->player, m->rotation_speed);
	else if (m->rotation_speed < 0)
		rotate_player_right(&game->player, -m->rotation_speed);
}

/**
 * @brief Handles player rotation based on mouse movement.
 *
 * This function calculates the distance of the mouse from the center of
 * the window and uses it to determine the rotation speed of the player.
 * It smooths rotation using a stored rotation speed between frames and
 * applies the appropriate rotation to the player.
 *
 * @param game Pointer to the game structure containing player data.
 * @param window Pointer to the window structure for size and mouse data.
 */
void	handle_mouse_movement(t_game *game, t_window *window)
{
	static double	stored_rotation_speed;
	t_mouse_data	m;

	m.sensitivity = 0.000009;
	m.center.x = window->size.x >> 1;
	m.center.y = window->size.y >> 1;
	mlx_mouse_get_pos(game->mlx, window->ptr, &m.position.x, &m.position.y);
	m.rotation_speed = stored_rotation_speed;
	update_rotation_speed(&m, game, window);
	apply_rotation(&m, game);
	stored_rotation_speed = m.rotation_speed;
}
