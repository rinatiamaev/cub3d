/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:49:24 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 11:17:58 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	move_forward(t_game *game, double move_speed)
{
	t_dpoint	next;

	next.x = game->player.pos.x + game->player.dir.x * move_speed;
	next.y = game->player.pos.y + game->player.dir.y * move_speed;
	if (can_move(game, next.x, next.y))
	{
		game->player.pos.x = next.x;
		game->player.pos.y = next.y;
	}
}

static void	move_backward(t_game *game, double move_speed)
{
	t_dpoint	next;

	move_speed *= -1;
	next.x = game->player.pos.x + game->player.dir.x * move_speed;
	next.y = game->player.pos.y + game->player.dir.y * move_speed;
	if (can_move(game, next.x, next.y))
	{
		game->player.pos.x = next.x;
		game->player.pos.y = next.y;
	}
}

static void	strafe_left(t_game *game, double move_speed)
{
	t_dpoint	strafe;
	t_dpoint	next;

	strafe.x = -game->player.dir.y;
	strafe.y = game->player.dir.x;
	next.x = game->player.pos.x + strafe.x * move_speed;
	next.y = game->player.pos.y + strafe.y * move_speed;
	if (can_move(game, next.x, next.y))
	{
		game->player.pos.x = next.x;
		game->player.pos.y = next.y;
	}
}

static void	strafe_right(t_game *game, double move_speed)
{
	t_dpoint	strafe;
	t_dpoint	next;

	strafe.x = game->player.dir.y;
	strafe.y = -game->player.dir.x;
	next.x = game->player.pos.x + strafe.x * move_speed;
	next.y = game->player.pos.y + strafe.y * move_speed;
	if (can_move(game, next.x, next.y))
	{
		game->player.pos.x = next.x;
		game->player.pos.y = next.y;
	}
}

void	handle_player_moves(t_game *game)
{
	struct timeval	tv;
	double			delta_time;
	double			current_time;
	static double	last_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	if (last_time == 0)
		last_time = current_time;
	delta_time = current_time - last_time;
	last_time = current_time;
	if (game->keys[UP])
		move_forward(game, game->player.move_speed);
	if (game->keys[DOWN])
		move_backward(game, game->player.move_speed);
	if (game->keys[LEFT])
		strafe_left(game, game->player.move_speed);
	if (game->keys[RIGHT])
		strafe_right(game, game->player.move_speed);
	if (game->keys[ARR_RIGHT])
		rotate_right(&game->player, game->player.rot_speed, delta_time);
	if (game->keys[ARR_LEFT])
		rotate_left(&game->player, game->player.rot_speed, delta_time);
}
