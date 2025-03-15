/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dial_phase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:46:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 16:18:14 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_dial_phase	get_witch_kitty_phase(t_story_state *story)
{
	if (!story->has_spoken_to_witch)
		return (PHASE_0);
	else if (story->sibling == SEARCHING && story->fireball == LOCATED)
		return (PHASE_1);
	else if (story->sibling == LOCATED)
		return (PHASE_2);
	else if (story->sibling == FOUND)
		return (PHASE_3);
	else if (story->sibling <= HELPED && story->fireball >= SAVED
		&& story->has_spoken_to_fire_spirit)
		return (PHASE_4);
	else if (story->sibling == SAVED)
		return (PHASE_5);
	else if (story->sibling == EXIT_SEARCH && story->key == FOUND)
		return (PHASE_6);
	else if (story->sibling == EXIT_SEARCH && story->exit == FOUND)
		return (PHASE_7);
	else if (story->key == FOUND && story->exit == FOUND)
		return (PHASE_8);
	return (IDLE);
}

t_dial_phase	get_calico_phase(t_story_state *story)
{
	if (!story->has_spoken_to_calico)
		return (PHASE_0);
	else if (story->fireball == SAVED)
		return (PHASE_1);
	else if (story->fireball == LOCATED && story->has_spoken_to_calico)
		return (PHASE_2);
	else if (story->fireball == SAVED && story->has_spoken_to_fire_spirit)
		return (PHASE_3);
	else if (story->sibling == SAVED && !story->has_spoken_to_fire_spirit)
		return (PHASE_4);
	else if (story->sibling == EXIT_SEARCH)
		return (PHASE_5);
	else if (story->sibling == EXIT_SEARCH && story->key == FOUND)
		return (PHASE_6);
	else if (story->sibling == EXIT_SEARCH && story->exit == FOUND)
		return (PHASE_7);
	else if (story->key == FOUND && story->exit == FOUND)
		return (PHASE_8);
	return (IDLE);
}

t_dial_phase	get_fire_spirit_phase(t_story_state *story)
{
	t_dial_phase	phase;

	phase = IDLE;
	if (story->fireball == SAVED)
		phase = PHASE_0;
	else if (story->exit == UNLOCKED)
		phase = PHASE_1;
	return (phase);
}
