/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:50:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:00:26 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if any NPC is currently speaking.
 *
 * Iterates through all NPCs in the game and returns true if any of them is
 * in the SPEAK state, meaning they are currently engaged in dialogue. If any
 * is talking movements for NPC and player are not authorized.
 *
 * @param game Pointer to the game structure.
 * @return true if at least one NPC is speaking, false otherwise.
 */
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
