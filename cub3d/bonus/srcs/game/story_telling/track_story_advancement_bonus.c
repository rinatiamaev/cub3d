/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_story_advancement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:08:04 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:41:39 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_key_story(t_game *game, t_item *key)
{
	t_story_state	*story;

	story = &game->story;
	if (story->key == NOT_STARTED
		&& has_line_of_sight(game, game->player.pos, key->pos))
		story->key = LOCATED;
	if (game->player.has_key)
		story->key = FOUND;
}

static void	update_exit_story(t_game *game)
{
	t_story_state	*story;

	story = &game->story;
	if (story->exit == NOT_STARTED
		&& has_line_of_sight(game, game->player.pos, game->exit_pos))
		story->exit = FOUND;
}

static void	update_npc_references(t_game *game, t_npc **calico, t_npc **witch,
														t_npc **fire_spirit)
{
	int	i;

	i = 0;
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

static void	update_item_references(t_game *game, t_item **key)
{
	int	i;

	i = 0;
	while (i < game->item_count)
	{
		if (ft_strcmp(game->items[i]->name, "key") == 0)
			*key = game->items[i];
		i++;
	}
}

void	update_story(t_game *game)
{
	t_npc	*calico;
	t_npc	*witch;
	t_npc	*fire_spirit;
	t_item	*key;

	calico = NULL;
	witch = NULL;
	fire_spirit = NULL;
	key = NULL;
	update_npc_references(game, &calico, &witch, &fire_spirit);
	update_item_references(game, &key);
	if (calico && witch && fire_spirit)
	{
		update_npc_story(game, calico, witch, fire_spirit);
		witch->dialogue.phase = get_witch_kitty_phase(&game->story);
		calico->dialogue.phase = get_calico_phase(&game->story);
		fire_spirit->dialogue.phase = get_fire_spirit_phase(&game->story);
	}
	if (key)
		update_key_story(game, key);
	update_exit_story(game);
}
