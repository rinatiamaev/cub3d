/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:49:24 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 23:12:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *player, t_map *map, double move_speed)
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

void	move_backward(t_player *player, t_map *map, double move_speed)
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

void	strafe_left(t_player *player, t_map *map, double move_speed)
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

void	strafe_right(t_player *player, t_map *map, double move_speed)
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
