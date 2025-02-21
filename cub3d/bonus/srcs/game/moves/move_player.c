/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:49:24 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/21 13:43:00 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_candidate_near_npc(t_dpoint candidate, t_npc *npc, 
	double min_distance)
{
	t_dpoint	dist;
	double	distance;
	
	dist.x = candidate.x - npc->pos.x;
	dist.y = candidate.y - npc->pos.y;
	distance = sqrt(dist.x * dist.x + dist.y * dist.y);
	return (distance < min_distance);
}

static bool	can_move(t_game *game, double next_x, double next_y)
{
	t_dpoint	candidate;

	candidate.x = next_x;
	candidate.y = next_y;

	// Check if the new position is inside a wall (1)
	if (game->map->matrix[(int)next_y][(int)next_x] == 1)
		return (false);

	// Check if the candidate position is too close to the NPC
	if (is_candidate_near_npc(candidate, game->witch_kitty, 1))
		return (false);

	// No collision, allow movement
	return (true);
}

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
	struct timeval tv;
	double current_time, delta_time;
	static double last_time = 0;

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
