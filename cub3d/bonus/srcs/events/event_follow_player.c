/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_follow_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:08:20 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 01:08:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	make_closest_npc_follow(t_game *game, double max_distance)
{
	t_npc	*npc;

	npc = find_closest_npc(game, max_distance);
	if (npc)
		npc->is_following = !npc->is_following;
}
