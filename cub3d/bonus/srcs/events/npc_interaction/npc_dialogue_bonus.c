/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_dialogue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:17:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 09:34:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	advance_npc_dialogue(t_npc *npc, t_story_state *story)
{
	if (npc->state != SPEAK)
		return (false);
	npc->dialogue.current_line++;
	if (npc->dialogue.current_line
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
	{
		if (ft_strcmp(npc->name, "witch kitty") == 0)
			story->has_spoken_to_witch = true;
		if (ft_strcmp(npc->name, "calico kitty") == 0)
			story->has_spoken_to_calico = true;
		if (ft_strcmp(npc->name, "fire spirit") == 0)
			story->has_spoken_to_fire_spirit = true;
		npc->dialogue.current_line = 0;
		npc->state = WAIT;
	}
	return (true);
}

bool	continue_npc_dialogue(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state != SPEAK)
		return (false);
	advance_npc_dialogue(npc, &game->story);
	return (true);
}

bool	handle_npc_dialogue(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state == SPEAK)
		return (false);
	npc->state = SPEAK;
	return (true);
}
