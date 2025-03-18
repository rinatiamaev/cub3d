/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc_follow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:57:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 09:38:03 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_npc_follow_path(t_game *game, t_npc *npc)
{
	a_star_path(game, npc, (t_point){(int)npc->pos.x, (int)npc->pos.y},
		(t_point){(int)game->player.last_pos.x, (int)game->player.last_pos.y});
}

static bool	is_follow_path_valid(t_npc *npc)
{
	return (npc->path && npc->path_length > 0);
}

void	move_npc_follow(t_game *game, t_npc *npc, double delta_time)
{
	t_dpoint	target;

	if (!is_follow_path_valid(npc))
	{
		update_npc_follow_path(game, npc);
		if (!is_follow_path_valid(npc))
			return;
	}
	target = npc->path[npc->path_index];
	if (move_npc(game, npc, target, delta_time))
	{
		npc->path_index++;
		if (npc->path_index >= npc->path_length)
		{
			update_npc_follow_path(game, npc);
			npc->path_index = 0;
		}
	}
}
