/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:28:44 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:34:16 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
