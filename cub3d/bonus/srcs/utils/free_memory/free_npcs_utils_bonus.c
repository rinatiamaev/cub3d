/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_npcs_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:52:52 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:55:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Frees the memory allocated for a NPC's waypoints.
 *
 * This function deallocates the memory used to store a list of patrol or
 * follow waypoints for the given NPC. It also nullifies the pointer to
 * prevent dangling references.
 *
 * @param npc Pointer to the NPC whose waypoints should be freed.
 */
void	free_npc_waypoints(t_npc *npc)
{
	if (npc->waypoints)
	{
		free(npc->waypoints);
		npc->waypoints = NULL;
	}
}
