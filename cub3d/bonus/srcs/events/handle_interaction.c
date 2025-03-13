/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:13:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 16:59:40 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	continue_npc_conversation(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state != SPEAK)
		return (false);
	advance_npc_dialogue(npc, &game->story);
	return (true);
}

void	handle_interaction(t_game *game)
{
	if (continue_npc_conversation(game))
		return ;
	if (!handle_npc_chase(game))
		return ;
	if (!interact_with_door(game))
		interact_with_npc(game);
}
