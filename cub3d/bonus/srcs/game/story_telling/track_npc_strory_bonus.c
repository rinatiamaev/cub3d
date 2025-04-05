/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_npc_strory_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:11:14 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:19:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Updates the progression of the sibling questline.
 *
 * This function controls the progression of the sibling (Calico kitty)
 * storyline based on:
 * - Dialogue with the witch.
 * - Line of sight between player and Calico.
 * - Interaction with the fire spirit.
 *
 * Transitions:
 * - NOT_STARTED -> SEARCHING after speaking to the witch.
 * - SEARCHING -> LOCATED when Calico is seen.
 * - LOCATED -> FOUND when Calico is seen AND fireball is located/saved.
 * - FOUND -> WAITING after initial dialogue.
 *
 * @param game   Pointer to the game state.
 * @param calico Pointer to Calico NPC.
 */
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

/**
 * @brief Handles sibling-related events tied to NPC interactions.
 *
 * This function reacts to events involving Calico, the witch, and the
 * fire spirit:
 * - Marks sibling as HELPED when fire spirit is hit.
 * - Marks sibling as SAVED when Calico sees the witch.
 * - Marks sibling as UNLOCKED once the player has the key and found the exit.
 *
 * It also updates NPC following behavior (can_follow, is_following).
 *
 * @param game         Pointer to the game state.
 * @param calico       Pointer to Calico NPC.
 * @param witch        Pointer to Witch NPC.
 * @param fire_spirit  Pointer to Fire Spirit NPC.
 */
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

/**
 * @brief Tracks the story progression of the fire spirit NPC.
 *
 * This function updates the fireball (fire spirit) storyline based on:
 * - Visibility by the player.
 * - Being splashed (is_hit).
 * - Player interaction.
 * - Story milestones (key and exit discovered).
 *
 * States:
 * - NOT_STARTED -> LOCATED -> SAVED -> EXIT_SEARCH -> UNLOCKED
 *
 * Enables following behavior once fully unlocked.
 *
 * @param game         Pointer to the game state.
 * @param fire_spirit  Pointer to Fire Spirit NPC.
 */
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

/**
 * @brief Updates the NPC story state progression.
 *
 * This function coordinates the global story state involving three key
 * NPCs (Calico, Witch, Fire Spirit). It delegates the handling of story
 * milestones such as:
 * - Calico's sibling storyline.
 * - Calico-Witch reunion.
 * - Fire Spirit rescue and follow behavior.
 *
 * It modifies story flags in `t_story_state` to reflect changes triggered
 * by player actions (dialogue, proximity, and item possession).
 *
 * It also updates dialogue phases dynamically for each NPC depending on
 * the current story state using:
 * - get_witch_kitty_phase()
 * - get_calico_phase()
 * - get_fire_spirit_phase()
 *
 * @param game         Pointer to the main game structure.
 * @param calico       Pointer to Calico Kitty NPC.
 * @param witch        Pointer to Witch Kitty NPC.
 * @param fire_spirit  Pointer to Fire Spirit NPC.
 */
void	update_npc_story(t_game *game, t_npc *calico, t_npc *witch,
														t_npc *fire_spirit)
{
	update_sibling_progression(game, calico);
	handle_sibling_events(game, calico, witch, fire_spirit);
	update_fireball_story(game, fire_spirit);
}
