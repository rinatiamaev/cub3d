/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:49:24 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/22 15:13:42 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	move_forward(t_game *game, double move_speed)
{
	t_dpoint	next_pos;

	next_pos.x = game->player.pos.x + game->player.dir.x * move_speed;
	next_pos.y = game->player.pos.y + game->player.dir.y * move_speed;
	if (is_position_valid_for_player(game, next_pos))
	{
		game->player.last_pos = game->player.pos;
		game->player.pos = next_pos;
	}
}

static void	move_backward(t_game *game, double move_speed)
{
	t_dpoint	next_pos;

	move_speed *= -1;
	next_pos.x = game->player.pos.x + game->player.dir.x * move_speed;
	next_pos.y = game->player.pos.y + game->player.dir.y * move_speed;
	if (is_position_valid_for_player(game, next_pos))
	{
		game->player.last_pos = game->player.pos;
		game->player.pos = next_pos;
	}
}

static void	strafe_left(t_game *game, double move_speed)
{
	t_dpoint	strafe;
	t_dpoint	next_pos;

	strafe.x = -game->player.dir.y;
	strafe.y = game->player.dir.x;
	next_pos.x = game->player.pos.x + strafe.x * move_speed;
	next_pos.y = game->player.pos.y + strafe.y * move_speed;
	if (is_position_valid_for_player(game, next_pos))
	{
		game->player.last_pos = game->player.pos;
		game->player.pos = next_pos;
	}
}

static void	strafe_right(t_game *game, double move_speed)
{
	t_dpoint	strafe;
	t_dpoint	next_pos;

	strafe.x = game->player.dir.y;
	strafe.y = -game->player.dir.x;
	next_pos.x = game->player.pos.x + strafe.x * move_speed;
	next_pos.y = game->player.pos.y + strafe.y * move_speed;
	if (is_position_valid_for_player(game, next_pos))
	{
		game->player.last_pos = game->player.pos;
		game->player.pos = next_pos;
	}
}

void	handle_player_moves(t_game *game, double delta_time)
{
	if (is_any_npc_talking(game))
		return ;
	if (game->keys[UP])
		move_forward(game, game->player.move_speed * delta_time);
	if (game->keys[DOWN])
		move_backward(game, game->player.move_speed * delta_time);
	if (game->keys[LEFT])
		strafe_left(game, game->player.move_speed * delta_time);
	if (game->keys[RIGHT])
		strafe_right(game, game->player.move_speed * delta_time);
	if (game->keys[ARR_RIGHT])
		rotate_right(&game->player, game->player.rot_speed, delta_time);
	if (game->keys[ARR_LEFT])
		rotate_left(&game->player, game->player.rot_speed, delta_time);
}
