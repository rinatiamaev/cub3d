/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_npc_strory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:11:14 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:39:53 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_sibling_progression(t_game *game, t_npc *calico)
{
	t_story_state	*story;

	story = &game->story;
	if (story->sibling == NOT_STARTED && story->has_spoken_to_witch)
		story->sibling = SEARCHING;
	if (story->sibling == SEARCHING
		&& has_line_of_sight(game, game->player.pos, calico->pos))
		story->sibling = LOCATED;
	if (story->sibling == LOCATED && story->fireball >= LOCATED
		&& story->has_spoken_to_calico)
		story->sibling = FOUND;
	if (story->sibling == FOUND)
		story->sibling = WAITING;
}

static void	handle_sibling_events(t_game *game, t_npc *calico, t_npc *witch,
														t_npc *fire_spirit)
{
	t_story_state	*story;

	story = &game->story;
	if (story->sibling < HELPED && fire_spirit->is_hit)
	{
		story->sibling = HELPED;
		calico->can_follow = true;
	}
	if (has_line_of_sight(game, calico->pos, witch->pos)
		&& story->sibling != UNLOCKED)
	{
		story->sibling = SAVED;
		calico->is_following = false;
		calico->can_follow = false;
	}
	if (story->sibling == SAVED
		&& story->key == FOUND && story->exit == FOUND)
	{
		story->sibling = UNLOCKED;
		calico->can_follow = true;
		witch->can_follow = true;
	}
}

static void	update_fireball_story(t_game *game, t_npc *fire_spirit)
{
	t_story_state	*story;
	t_player		*player;

	story = &game->story;
	player = &game->player;
	if (story->fireball == NOT_STARTED
		&& has_line_of_sight(game, player->pos, fire_spirit->pos))
		story->fireball = LOCATED;
	if (story->fireball == LOCATED
		&& fire_spirit->is_hit)
		story->fireball = SAVED;
	if (story->fireball == SAVED
		&& story->has_spoken_to_fire_spirit)
		story->fireball = EXIT_SEARCH;
	if (story->fireball == EXIT_SEARCH
		&& story->key == FOUND && story->exit == FOUND)
	{
		story->fireball = UNLOCKED;
		fire_spirit->can_follow = true;
	}
}

void	update_npc_story(t_game *game, t_npc *calico, t_npc *witch,
														t_npc *fire_spirit)
{
	update_sibling_progression(game, calico);
	handle_sibling_events(game, calico, witch, fire_spirit);
	update_fireball_story(game, fire_spirit);
}
