/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:49:24 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 14:20:08 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward(t_player *player, t_map *map, double move_speed)
{
	t_dpoint	next;

	next.x = player->pos.x + player->dir.x * move_speed;
	next.y = player->pos.y;
	if (map->matrix[(int)next.y][(int)next.x] != 1)
		player->pos.x = next.x;
	next.x = player->pos.x;
	next.y = player->pos.y + player->dir.y * move_speed;
	if (map->matrix[(int)next.y][(int)next.x] != 1)
		player->pos.y = next.y;
}

static void	move_backward(t_player *player, t_map *map, double move_speed)
{
	t_dpoint	next;

	move_speed *= -1;
	next.x = player->pos.x + player->dir.x * move_speed;
	next.y = player->pos.y;
	if (map->matrix[(int)next.y][(int)next.x] != 1)
		player->pos.x = next.x;
	next.x = player->pos.x;
	next.y = player->pos.y + player->dir.y * move_speed;
	if (map->matrix[(int)next.y][(int)next.x] != 1)
		player->pos.y = next.y;
}

static void	strafe_left(t_player *player, t_map *map, double move_speed)
{
	t_dpoint	strafe;
	t_dpoint	next;

	strafe.x = -player->dir.y;
	strafe.y = player->dir.x;
	next.x = player->pos.x + strafe.x * move_speed;
	next.y = player->pos.y;
	if (map->matrix[(int)next.y][(int)next.x] != 1)
		player->pos.x = next.x;
	next.x = player->pos.x;
	next.y = player->pos.y + strafe.y * move_speed;
	if (map->matrix[(int)next.y][(int)next.x] != 1)
		player->pos.y = next.y;
}

static void	strafe_right(t_player *player, t_map *map, double move_speed)
{
	t_dpoint	strafe;
	t_dpoint	next;

	strafe.x = player->dir.y;
	strafe.y = -player->dir.x;
	next.x = player->pos.x + strafe.x * move_speed;
	next.y = player->pos.y;
	if (map->matrix[(int)next.y][(int)next.x] != 1)
		player->pos.x = next.x;
	next.x = player->pos.x;
	next.y = player->pos.y + strafe.y * move_speed;
	if (map->matrix[(int)next.y][(int)next.x] != 1)
		player->pos.y = next.y;
}

void	handle_player_moves(t_game *game)
{
	if (game->keys[UP])
		move_forward(&game->player, game->map, game->player.move_speed);
	if (game->keys[DOWN])
		move_backward(&game->player, game->map, game->player.move_speed);
	if (game->keys[LEFT])
		strafe_left(&game->player, game->map, game->player.move_speed);
	if (game->keys[RIGHT])
		strafe_right(&game->player, game->map, game->player.move_speed);
	if (game->keys[ARR_RIGHT])
		rotate_right(&game->player, game->player.rot_speed);
	if (game->keys[ARR_LEFT])
		rotate_left(&game->player, game->player.rot_speed);
}
