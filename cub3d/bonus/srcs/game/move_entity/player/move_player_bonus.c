/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:42:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:33:07 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	move_player_forward(t_game *game, t_player *player,
											double delta_time)
{
	move_player(game, player, player->facing_dir, delta_time);
}

void	move_player_backward(t_game *game, t_player *player,
											double delta_time)
{
	t_dpoint	backward_direction;

	backward_direction.x = -player->facing_dir.x;
	backward_direction.y = -player->facing_dir.y;
	move_player(game, player, backward_direction, delta_time);
}

void	strafe_player_left(t_game *game, t_player *player,
											double delta_time)
{
	t_dpoint	strafe_left_direction;

	strafe_left_direction.x = -player->facing_dir.y;
	strafe_left_direction.y = player->facing_dir.x;
	move_player(game, player, strafe_left_direction, delta_time);
}

void	strafe_player_right(t_game *game, t_player *player,
											double delta_time)
{
	t_dpoint	strafe_right_direction;

	strafe_right_direction.x = player->facing_dir.y;
	strafe_right_direction.y = -player->facing_dir.x;
	move_player(game, player, strafe_right_direction, delta_time);
}
