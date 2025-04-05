/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_move_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:28:44 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:14:41 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Handles player movement based on key inputs.
 *
 * This function checks the state of various keys and moves the player
 * accordingly. It also ensures that the player cannot move while an NPC
 * is talking.
 *
 * @param game Pointer to the game structure.
 * @param delta_time Time elapsed since last frame.
 */
void	handle_player_moves(t_game *game, double delta_time)
{
	t_player	*player;

	player = &game->player;
	if (is_any_npc_talking(game))
		return ;
	if (game->keys[UP])
		move_player_forward(game, player, delta_time);
	if (game->keys[DOWN])
		move_player_backward(game, player, delta_time);
	if (game->keys[LEFT])
		strafe_player_left(game, player, delta_time);
	if (game->keys[RIGHT])
		strafe_player_right(game, player, delta_time);
	if (game->keys[ARR_RIGHT])
		rotate_player_right(player, delta_time);
	if (game->keys[ARR_LEFT])
		rotate_player_left(player, delta_time);
}
