/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_story_advancement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:08:04 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/19 14:04:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_sibling_story(t_game *game, t_npc *calico, t_npc *witch, t_npc *fire_spirit)
{
	t_story_state	*story = &game->story;

	if (story->sibling == NOT_STARTED && story->has_spoken_to_witch)
		story->sibling = SEARCHING;

	if (story->sibling == SEARCHING && has_line_of_sight(game, game->player.pos, calico->pos))
		story->sibling = LOCATED;

	if (story->sibling == LOCATED && story->fireball >= LOCATED && story->has_spoken_to_calico)
		story->sibling = FOUND;

	if (story->sibling == FOUND)
		story->sibling = WAITING;

	if (story->sibling < HELPED && fire_spirit->is_hit)
	{
		story->sibling = HELPED;
		calico->can_follow = true;
	}

	if (story->sibling == HELPED && has_line_of_sight(game, calico->pos, witch->pos))
	{
		story->sibling = SAVED;
		calico->can_follow = false;
	}

	if (story->sibling == SAVED && story->key == FOUND)
		story->sibling = EXIT_SEARCH;

	if (story->sibling == EXIT_SEARCH && story->exit == FOUND)
	{
		story->sibling = UNLOCKED;
		calico->can_follow = true;
		witch->can_follow = true;
	}
}

static void update_fireball_story(t_game *game, t_npc *fire_spirit)
{
	t_story_state *story = &game->story;
	t_player *player = &game->player;

	if (story->fireball == NOT_STARTED && has_line_of_sight(game, player->pos, fire_spirit->pos))
		story->fireball = LOCATED;

	if (story->fireball == LOCATED && fire_spirit->is_hit)
		story->fireball = SAVED;

	if (story->fireball == SAVED && story->has_spoken_to_fire_spirit)
		story->fireball = EXIT_SEARCH;

	if (story->fireball == EXIT_SEARCH && story->key == FOUND && story->exit == FOUND)
	{
		story->fireball = UNLOCKED;
		fire_spirit->can_follow = true;
	}
}

/* static void update_exit_story(t_game *game)
{
	t_story_state *story = &game->story;

	if (story->exit == NOT_STARTED && has_line_of_sight(game, game->player.pos, game->exit.pos))
		story->exit = FOUND;
}

static void update_key_story(t_game *game)
{
	t_story_state *story = &game->story;

	if (story->key == NOT_STARTED && has_line_of_sight(game, game->player.pos, game->key.pos))
		story->key = LOCATED;
	else if (game->player.has_key && story->key == LOCATED)
		story->key = FOUND;
} */

static void	update_npc_references(t_game *game, t_npc **calico, t_npc **witch, t_npc **fire_spirit)
{
	int i = 0;

	while (i < game->npc_count)
	{
		if (ft_strcmp(game->npcs[i]->name, "calico kitty") == 0)
			*calico = game->npcs[i];
		else if (ft_strcmp(game->npcs[i]->name, "witch kitty") == 0)
			*witch = game->npcs[i];
		else if (ft_strcmp(game->npcs[i]->name, "fire spirit") == 0)
			*fire_spirit = game->npcs[i];
		i++;
	}
}

void	update_story(t_game *game)
{
	t_npc	*calico = NULL;
	t_npc	*witch = NULL;
	t_npc	*fire_spirit = NULL;

	update_npc_references(game, &calico, &witch, &fire_spirit);

	if (calico && witch && fire_spirit)
	{
		update_fireball_story(game, fire_spirit);
		update_sibling_story(game, calico, witch, fire_spirit);

		witch->dialogue.phase = get_witch_kitty_phase(&game->story);
		calico->dialogue.phase = get_calico_phase(&game->story);
		fire_spirit->dialogue.phase = get_fire_spirit_phase(&game->story);
	}
}
