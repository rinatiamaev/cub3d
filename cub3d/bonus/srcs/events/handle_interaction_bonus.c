/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_interaction_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:13:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:42:56 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Tries to interact with nearby entities sorted by proximity.
 *
 * Iterates over all entities (NPCs and items), checking if they are within
 * interaction range (2.0 units) and in the player's line of sight. If a valid
 * interaction is possible, the corresponding function is called.
 *
 * @param game Pointer to the game structure.
 * @return true if any entity interaction was successful, false otherwise.
 */
static bool	interact_with_sorted_entities(t_game *game)
{
	t_entity	*entity;
	double		interaction_range;
	double		dist;
	int			i;

	interaction_range = 2.0;
	i = -1;
	while (++i < game->entity_count)
	{
		entity = &game->entities[i];
		dist = ft_euclidean_dist_dpoint(game->player.pos, entity->pos);
		if (dist > interaction_range)
			continue ;
		if (!is_facing_target(&game->player, entity->pos))
			continue ;
		if (entity->type == ITEM && interact_with_item(game))
			return (true);
		if (entity->type == NPC && interact_with_npc(game))
			return (true);
	}
	return (false);
}

/**
 * @brief Handles player interaction logic with NPCs, items, and doors.
 *
 * Attempts to continue an ongoing NPC dialogue first. If not applicable,
 * checks for nearby interactable entities (NPCs or items) and handles them.
 * If no interaction occurs and the player is chased by an enemy NPC,
 * applies the splash effect if water is available. Finally, tries to
 * interact with nearby doors.
 *
 * @param game Pointer to the game structure.
 */
void	handle_interaction(t_game *game)
{
	if (continue_npc_dialogue(game))
		return ;
	if (interact_with_sorted_entities(game))
		return ;
	if (!handle_npc_chase(game))
		return ;
	interact_with_door(game);
}
