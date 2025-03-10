/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:25:26 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 23:53:24 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_player_near_npc(t_npc *npc, t_player *player, double range)
{
	return (ft_cab_dist_dpoint(player->pos, npc->pos) < range);
}
