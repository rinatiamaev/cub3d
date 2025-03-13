/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_npcs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:52:52 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 15:52:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_npc_waypoints(t_npc *npc)
{
	if (npc->waypoints)
	{
		free(npc->waypoints);
		npc->waypoints = NULL;
	}
}
