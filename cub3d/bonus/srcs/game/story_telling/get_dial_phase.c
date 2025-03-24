/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dial_phase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:46:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 16:07:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_dial_phase	get_witch_kitty_phase(t_story_state *story)
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

t_dial_phase	get_calico_phase(t_story_state *story)
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

t_dial_phase	get_fire_spirit_phase(t_story_state *story)
{
	if (!story->has_spoken_to_fire_spirit)
		return (PHASE_0);
	else if (story->fireball == UNLOCKED)
		return (PHASE_1);
	return (IDLE);
}
