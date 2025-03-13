/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_story_advancement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:08:04 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 14:12:07 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void update_sibling(t_game *game, t_npc *calico, t_npc *witch,
	t_npc *fire_spirit)
{
	t_story_state	*story;

	story = &game->story;
	if (story->sibling == NOT_STARTED
		&& story->has_spoken_to_witch)
		story->sibling = SEARCHING;
	else if (story->sibling >= SEARCHING && story->fireball >= LOCATED
		&& story->has_spoken_to_calico)
	{
		story->sibling = FOUND;
		story->fireball = LOCATED;
	}
	else if (has_line_of_sight(game, game->player.pos, calico->pos))
		story->sibling = LOCATED;
	else if (story->sibling == FOUND)
		story->sibling = WAITING;
	else if (story->sibling < HELPED && fire_spirit->is_hit)
		story->sibling = HELPED;
	else if (story->sibling == HELPED && has_line_of_sight(game, calico->pos, witch->pos))
		story->sibling = SAVED;
	else if (story->sibling == SAVED && story->key == FOUND)
		story->sibling = EXIT_SEARCH;
	else if (story->sibling == EXIT_SEARCH && story->exit == FOUND)
		story->sibling = UNLOCKED;
}

static void update_fireball(t_game *game, t_story_state *story,
											t_player *player, t_npc *npc)
{
	if (story->fireball < LOCATED
		&& has_line_of_sight(game, player->pos, npc->pos))
		story->fireball = LOCATED;
	if (story->fireball < SAVED
		&& npc->is_hit)
		story->fireball = SAVED;
	if (story->fireball < EXIT_SEARCH
		&& story->has_spoken_to_fire_spirit)
		story->fireball = EXIT_SEARCH;
}

void update_story(t_game *game)
{
	t_npc *calico      = NULL;
	t_npc *witch       = NULL;
	t_npc *fire_spirit = NULL;

	for (int i = 0; i < game->npc_count; i++)
	{
		if (ft_strcmp(game->npcs[i]->name, "calico kitty") == 0)
			calico = game->npcs[i];
		else if (ft_strcmp(game->npcs[i]->name, "witch kitty") == 0)
			witch = game->npcs[i];
		else if (ft_strcmp(game->npcs[i]->name, "fire spirit") == 0)
			fire_spirit = game->npcs[i];
	}
	update_sibling(game, calico, witch, fire_spirit);
	update_fireball(game, &game->story, &game->player, fire_spirit);
	witch->dialogue.phase = get_witch_kitty_phase(&game->story);
	calico->dialogue.phase = get_calico_phase(&game->story);
	fire_spirit->dialogue.phase = get_fire_spirit_phase(&game->story);
}

