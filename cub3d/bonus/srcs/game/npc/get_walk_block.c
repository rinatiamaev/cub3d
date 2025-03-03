/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_walk_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:08:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/02 14:19:30 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	get_angle_difference(double angle_move, double angle_player)
{
	double	diff;

	diff = angle_move - angle_player;
	while (diff < -M_PI)
		diff += 2 * M_PI;
	while (diff > M_PI)
		diff -= 2 * M_PI;
	return (diff);
}

static double	calculate_npc_angle(t_npc *npc)
{
	if (fabs(npc->move_vec.x) > 0.0001 || fabs(npc->move_vec.y) > 0.0001)
		npc->last_move_vec = npc->move_vec;
	return (atan2(npc->last_move_vec.y, npc->last_move_vec.x));
}

static double	calculate_player_angle(t_npc *npc, t_player *player)
{
	t_dpoint	delta;

	delta = (t_dpoint){player->pos.x - npc->pos.x, player->pos.y - npc->pos.y};
	return (atan2(delta.y, delta.x));
}

static int	assign_walk_block(double deg)
{
	if (deg >= 0 && deg < 45)
		return (WALK_TOWARD);
	else if (deg >= 45 && deg < 135)
		return (WALK_LEFT);
	else if (deg >= 135 && deg < 225)
		return (WALK_AWAY);
	else if (deg >= 225 && deg < 315)
		return (WALK_RIGHT);
	else
		return (WALK_TOWARD);
}

int	get_walk_block(t_npc *npc, t_player *player)
{
	static int		last_block;
	double			angle_move;
	double			angle_player;
	double			diff;
	double			deg;

	last_block = WALK_TOWARD;
	angle_move = calculate_npc_angle(npc);
	angle_player = calculate_player_angle(npc, player);
	diff = get_angle_difference(angle_move, angle_player);
	deg = diff * (180.0 / M_PI);
	if (deg < 0)
		deg += 360.0;
	if (fabs(deg - last_block) < DEAD_ZONE)
		return (last_block);
	last_block = assign_walk_block(deg);
	return (last_block);
}
