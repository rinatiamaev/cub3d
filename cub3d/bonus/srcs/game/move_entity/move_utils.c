/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:50:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 20:28:33 by nlouis           ###   ########.fr       */
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

bool	is_position_occupied_by_other_npc(t_game *game, t_npc *npc,
													t_dpoint next_pos)
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
		if (ft_cab_dist_dpoint(game->npcs[i]->pos, next_pos) < 0.5)
			return (true);
		i++;
	}
	return (false);
}
