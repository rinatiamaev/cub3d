/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:46:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 16:07:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Determines the current dialogue phase for Witch Kitty.
 *
 * This function analyzes the story progression to assign the appropriate
 * dialogue phase for the Witch NPC. It uses flags such as whether the
 * player has spoken to the Witch, the sibling storyline status, and the
 * fireball storyline.
 *
 * The returned phase reflects the Witch's awareness of the world state and
 * determines which dialogue lines she should present to the player.
 *
 * @param story Pointer to the current story state.
 * @return Dialogue phase identifier (PHASE_0..PHASE_6 or IDLE).
 */
t_dp	get_witch_kitty_phase(t_story_state *story)
{
	if (!story->has_spoken_to_witch)
		return (PHASE_0);
	else if (story->sibling == SEARCHING && story->fireball >= LOCATED)
		return (PHASE_1);
	else if (story->sibling == LOCATED)
		return (PHASE_2);
	else if (story->sibling == FOUND || story->sibling == WAITING)
		return (PHASE_3);
	else if (story->fireball >= LOCATED && story->fireball < SAVED)
		return (PHASE_4);
	else if (story->sibling == SAVED
		&& (story->key != FOUND || story->exit != FOUND))
		return (PHASE_5);
	else if (story->sibling == UNLOCKED)
		return (PHASE_6);
	return (IDLE);
}

/**
 * @brief Determines the current dialogue phase for Calico Kitty.
 *
 * Based on the progression of the fireball and sibling storylines,
 * this function assigns a dialogue phase for Calico. These phases
 * reflect Calico’s emotional and narrative state as the story unfolds.
 *
 * If the player hasn’t spoken to Calico yet, PHASE_0 is returned.
 *
 * @param story Pointer to the current story state.
 * @return Dialogue phase identifier (PHASE_0..PHASE_5 or IDLE).
 */
t_dp	get_calico_phase(t_story_state *story)
{
	if (!story->has_spoken_to_calico)
		return (PHASE_0);
	else if (story->fireball == LOCATED)
		return (PHASE_1);
	else if (story->sibling < SAVED && story->fireball == EXIT_SEARCH)
		return (PHASE_2);
	else if (story->sibling < SAVED && story->fireball == SAVED)
		return (PHASE_3);
	else if (story->sibling == SAVED)
		return (PHASE_4);
	else if (story->sibling == UNLOCKED)
		return (PHASE_5);
	return (IDLE);
}

/**
 * @brief Determines the current dialogue phase for Fire Spirit.
 *
 * Returns PHASE_0 if the Fire Spirit has not been spoken to yet.
 * If the player has helped the Fire Spirit and the exit/key are
 * found, the Fire Spirit transitions to PHASE_1, ready to follow.
 *
 * @param story Pointer to the current story state.
 * @return Dialogue phase identifier (PHASE_0..PHASE_1 or IDLE).
 */
t_dp	get_fire_spirit_phase(t_story_state *story)
{
	if (!story->has_spoken_to_fire_spirit)
		return (PHASE_0);
	else if (story->fireball == UNLOCKED)
		return (PHASE_1);
	return (IDLE);
}
