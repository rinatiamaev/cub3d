/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_npc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:09:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 20:15:49 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_npc	*find_closest_npc(t_game *game, double max_distance)
{
	t_npc	*closest_npc;
	double	closest_dist;
	double	current_dist;
	int		i;

	closest_npc = NULL;
	closest_dist = max_distance;
	i = 0;
	while (i < game->npc_count)
	{
		current_dist
			= ft_cab_dist_dpoint(game->player.pos, game->npcs[i]->pos);
		if (current_dist < closest_dist)
		{
			closest_dist = current_dist;
			closest_npc = game->npcs[i];
		}
		i++;
	}
	return (closest_npc);
}

bool	advance_npc_dialogue(t_npc *npc)
{
	if (npc->state != NPC_STATE_SPEAK)
		return (false);
	npc->current_line++;
	if (npc->current_line >= npc->line_count)
	{
		npc->current_line = 0;
		npc->state = NPC_STATE_WAIT;
	}
	return (true);
}

static bool	handle_npc_chase(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 4.0);
	if (npc && npc->state == NPC_STATE_CHASE
		&& game->player.has_water)
	{
			npc->is_hit = true;
			return (false);
	}
	return (true);
}

static bool	handle_npc_speak(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state == NPC_STATE_SPEAK)
		return (false);
	npc->state = NPC_STATE_SPEAK;
	return (true);
}

bool	interact_with_npc(t_game *game)
{
	if (!handle_npc_chase(game))
		return (false);
	return (handle_npc_speak(game));
}

