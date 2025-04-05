/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:42:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/05 20:00:17 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Moves the player in the specified direction if the move is valid.
 *
 * This function calculates the movement step based on the player's speed
 * and delta time, computes the next position, and checks if the move is
 * allowed. If valid, updates the player's position and stores the last one.
 *
 * @param game Pointer to the game structure.
 * @param player Pointer to the player structure.
 * @param direction Normalized direction vector of movement.
 * @param delta_time Time elapsed since last frame.
 */
static void	move_player(t_game *game, t_player *player,
									t_dpoint direction, double delta_time)
{
	t_dpoint	step;
	t_dpoint	next_pos;

	if (delta_time > 0.1)
		delta_time = 0.1;
	step.x = direction.x * player->move_speed * delta_time;
	step.y = direction.y * player->move_speed * delta_time;
	next_pos.x = player->pos.x + step.x;
	next_pos.y = player->pos.y + step.y;
	if (is_player_move_valid(game, next_pos))
	{
		player->last_pos = player->pos;
		player->pos = next_pos;
	}
}

/**
 * @brief Moves the player forward based on their facing direction.
 *
 * @param game Pointer to the game structure.
 * @param player Pointer to the player structure.
 * @param delta_time Time elapsed since last frame.
 */
void	move_player_forward(t_game *game, t_player *player,
											double delta_time)
{
	move_player(game, player, player->facing_dir, delta_time);
}

/**
 * @brief Moves the player to the left (strafe) based on their facing direction
 *
 * @param game Pointer to the game structure.
 * @param player Pointer to the player structure.
 * @param delta_time Time elapsed since last frame.
 */
void	move_player_backward(t_game *game, t_player *player,
											double delta_time)
{
	t_dpoint	backward_direction;

	backward_direction.x = -player->facing_dir.x;
	backward_direction.y = -player->facing_dir.y;
	move_player(game, player, backward_direction, delta_time);
}

/**
 * @brief Moves the player to the left (strafe) based on their facing direction
 *
 * @param game Pointer to the game structure.
 * @param player Pointer to the player structure.
 * @param delta_time Time elapsed since last frame.
 */
void	strafe_player_left(t_game *game, t_player *player,
											double delta_time)
{
	t_dpoint	strafe_left_direction;

	strafe_left_direction.x = -player->facing_dir.y;
	strafe_left_direction.y = player->facing_dir.x;
	move_player(game, player, strafe_left_direction, delta_time);
}

/**
 * @brief Moves the player to the right (strafe) based on their facing direction
 *
 * @param game Pointer to the game structure.
 * @param player Pointer to the player structure.
 * @param delta_time Time elapsed since last frame.
 */
void	strafe_player_right(t_game *game, t_player *player,
											double delta_time)
{
	t_dpoint	strafe_right_direction;

	strafe_right_direction.x = player->facing_dir.y;
	strafe_right_direction.y = -player->facing_dir.x;
	move_player(game, player, strafe_right_direction, delta_time);
}
