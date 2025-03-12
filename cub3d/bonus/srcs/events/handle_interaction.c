/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:13:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/11 22:01:28 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_interaction(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (npc && npc->state == SPEAK)
		advance_npc_dialogue(npc);
	else if (!interact_with_npc(game))
		interact_with_door(game);
}
