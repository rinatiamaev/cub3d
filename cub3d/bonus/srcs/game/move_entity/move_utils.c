/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:50:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/12 10:09:00 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_any_npc_talking(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->npc_count)
	{
		if (game->npcs[i]->state == SPEAK)
			return (true);
		i++;
	}
	return (false);
}

/* bool	is_target_occupied_by_npc(t_game *game, t_npc *npc, t_point target)
{
	int i;

	i = 0;
	while (i < game->npc_count)
	{
		if (game->npcs[i] == npc)
		{
			i++;
			continue ;
		}
		if (game->npcs[i]->pos.x == target.x
			&& game->npcs[i]->pos.y == target.y)
			return (true);
		i++;
	}
	return (false);
} */