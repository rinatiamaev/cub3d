/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_story_advancement_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:08:04 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:17:49 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Updates the story state related to the key item.
 *
 * This function checks if the player has seen or collected the key item
 * and updates the corresponding `story->key` state.
 * 
 * - If the player has line of sight to the key, it is marked as LOCATED.
 * - If the player has picked it up, it is marked as FOUND.
 *
 * @param game Pointer to the game context.
 * @param key  Pointer to the key item.
 */
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

/**
 * @brief Updates the story state related to the exit door.
 *
 * If the player has line of sight to the exit door and it hasn't been
 * discovered yet, the exit state is marked as FOUND.
 *
 * @param game Pointer to the game context.
 */
static void	update_exit_story(t_game *game)
{
	t_story_state	*story;

	story = &game->story;
	if (story->exit == NOT_STARTED
		&& has_line_of_sight(game, game->player.pos, game->exit_pos))
		story->exit = FOUND;
}

/**
 * @brief Assigns references to main NPCs by matching their names.
 *
 * Iterates through all NPCs and stores pointers to specific NPCs
 * (calico kitty, witch kitty, fire spirit) based on their name.
 *
 * @param game         Pointer to the game context.
 * @param calico       Output pointer to calico kitty NPC.
 * @param witch        Output pointer to witch kitty NPC.
 * @param fire_spirit  Output pointer to fire spirit NPC.
 */
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

/**
 * @brief Finds the key item in the item list.
 *
 * Iterates through the list of items and stores a pointer to the
 * key item if found. Used for story tracking purposes.
 *
 * @param game Pointer to the game context.
 * @param key  Output pointer to the key item.
 */
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

/**
 * @brief Updates the progression of the main story elements.
 *
 * This function synchronizes the story state with the current state of
 * the game world. It performs the following tasks:
 *
 * 1. Locates and assigns references to main NPCs and key item.
 * 2. Updates the story state based on whether the player has seen or
 *    interacted with key story objects (key, exit, NPCs).
 * 3. Sets the dialogue phase of the main NPCs according to story progress.
 *
 * The function ensures that all dynamic narrative conditions are kept in sync
 * with player actions and visibility.
 *
 * @param game Pointer to the game context.
 */
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
