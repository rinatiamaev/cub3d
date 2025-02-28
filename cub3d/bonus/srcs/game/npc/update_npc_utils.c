/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:25:26 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/01 01:26:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_player_near_npc(t_npc *npc, t_player *player, double near_distance)
{
	t_dpoint	delta;
	double		dist_sq;

	delta.x = player->pos.x - npc->pos.x;
	delta.y = player->pos.y - npc->pos.y;
	dist_sq = delta.x * delta.x + delta.y * delta.y;
	return (dist_sq < (near_distance * near_distance));
}
