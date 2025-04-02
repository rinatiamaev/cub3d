/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_npc_follow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:57:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:31:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_npc_follow_path(t_game *game, t_player *player, t_npc *npc)
{
	t_point	start;
	t_point	goal;

	start = (t_point){(int)npc->pos.x, (int)npc->pos.y};
	goal = (t_point){(int)player->last_pos.x, (int)player->last_pos.y};
	a_star_path(game, npc, start, goal);
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
		update_npc_follow_path(game, &game->player, npc);
		if (!is_follow_path_valid(npc))
			return ;
	}
	target = npc->path[npc->path_index];
	if (move_npc(game, npc, target, delta_time))
	{
		npc->path_index++;
		if (npc->path_index >= npc->path_length)
		{
			update_npc_follow_path(game, &game->player, npc);
			npc->path_index = 0;
		}
	}
}
