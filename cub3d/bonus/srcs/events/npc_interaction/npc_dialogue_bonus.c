/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_dialogue_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:17:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:05:19 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Advances the dialogue of the given NPC.
 *
 * This function increments the current line of dialogue for the specified
 * NPC. If the end of the dialogue is reached, it resets the line and sets
 * the NPC state to WAIT. It also updates the story state based on the NPC
 * spoken to.
 *
 * @param npc Pointer to the NPC whose dialogue is being advanced.
 * @param story Pointer to the game story state.
 * @return true if dialogue was advanced, false otherwise.
 */
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

/**
 * @brief Continues the dialogue with the closest NPC if in speaking range.
 *
 * This function checks if the player is currently in a dialogue state with
 * a nearby NPC (within a fixed range). If so, it advances the dialogue
 * and returns true. All the NPCs and the player can not move while the
 * player is in a dialogue.
 *
 * @param game Pointer to the game context.
 * @return true if dialogue was continued, false otherwise.
 */
bool	continue_npc_dialogue(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state != SPEAK)
		return (false);
	advance_npc_dialogue(npc, &game->story);
	return (true);
}

/**
 * @brief Initiates dialogue with the closest NPC if not already speaking.
 *
 * This function checks if the player is within a certain range of an NPC
 * and initiates dialogue with that NPC. If the NPC is already in a speaking
 * state, it does nothing. If the player is already in a dialogue with a NPC,
 * the situation is handled in the `continue_npc_dialogue` function.
 *
 * @param game Pointer to the game context.
 * @return true if dialogue was initiated, false otherwise.
 */
bool	handle_npc_dialogue(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state == SPEAK)
		return (false);
	npc->state = SPEAK;
	return (true);
}
