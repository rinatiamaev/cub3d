/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_item_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:48:46 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:14:00 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Finds the closest item within a given range that the player is facing
 *
 * This function iterates through all items in the game and returns the closest
 * one that is within the specified range and in the player's field of view.
 *
 * @param game Pointer to the game context.
 * @param range Maximum distance within which the item can be considered.
 * @return Pointer to the closest valid item, or NULL if none is found.
 */
static t_item	*find_closest_item(t_game *game, double range)
{
	t_item	*closest_item;
	double	min_distance;
	double	current_distance;
	int		i;

	closest_item = NULL;
	min_distance = range;
	i = 0;
	while (i < game->item_count)
	{
		current_distance
			= ft_euclidean_dist_dpoint(game->player.pos, game->items[i]->pos);
		if (current_distance <= min_distance
			&& is_facing_target(&game->player, game->items[i]->pos))
		{
			min_distance = current_distance;
			closest_item = game->items[i];
		}
		i++;
	}
	return (closest_item);
}

/**
 * @brief Handles removal of the last remaining item from the item list.
 *
 * This function frees the specified item, then resets the item list
 * by freeing the array and setting the count to zero.
 *
 * @param game Pointer to the game context.
 * @param item_to_remove Pointer to the item to be removed.
 */
static void	handle_single_item_removal(t_game *game, t_item *item_to_remove)
{
	free_single_item(game, item_to_remove);
	free(game->items);
	game->items = NULL;
	game->item_count = 0;
}

/**
 * @brief Creates a new item list excluding the specified item.
 *
 * This function allocates memory for a new list of items, copies all items
 * from the original list except the specified one, and frees the original list.
 *
 * @param game Pointer to the game context.
 * @param item_to_remove Pointer to the item to be removed.
 * @return Pointer to the new list of items.
 */
static t_item	**create_new_item_list(t_game *game, t_item *item_to_remove)
{
	t_item	**new_list;
	int		i;
	int		j;

	new_list = x_calloc(game, game->item_count - 1, sizeof(t_item *));
	i = 0;
	j = 0;
	while (i < game->item_count)
	{
		if (game->items[i] != item_to_remove)
		{
			new_list[j] = game->items[i];
			j++;
		}
		else
			free_single_item(game, game->items[i]);
		i++;
	}
	return (new_list);
}

/**
 * @brief Removes an item from the game item list.
 *
 * This function handles the removal of an item from the game. If the item
 * is the last one in the list, it frees the list and resets the count.
 * Otherwise, it creates a new list without the specified item.
 *
 * @param game Pointer to the game context.
 * @param item_to_remove Pointer to the item to be removed.
 */
static void	remove_item_from_list(t_game *game, t_item *item_to_remove)
{
	t_item	**new_list;

	if (game->item_count <= 1)
	{
		handle_single_item_removal(game, item_to_remove);
		return ;
	}
	new_list = create_new_item_list(game, item_to_remove);
	free(game->items);
	game->items = new_list;
	game->item_count--;
}

/**
 * @brief Handles the interaction between the player and the closest item.
 *
 * Checks if the player is close enough to an item and facing it.
 * If the item is collectible and hasn't been collected, it's added to the
 * player’s inventory and removed from the world.
 * Special interaction is handled for the "well" item, allowing the player
 * to fill a bucket with water.
 *
 * @param game Pointer to the game context.
 * @return true If the player successfully interacted with an item.
 * @return false If no valid interaction occurred.
 */
bool	interact_with_item(t_game *game)
{
	t_item	*item;

	item = find_closest_item(game, 1.5);
	if (!item)
		return (false);
	if (item->is_collectible && !item->is_collected)
	{
		item->is_collected = true;
		if (ft_strcmp(item->name, "bucket") == 0)
			game->player.has_bucket = true;
		if (ft_strcmp(item->name, "key") == 0)
			game->player.has_key = true;
		remove_item_from_list(game, item);
		return (true);
	}
	else if (ft_strcmp(item->name, "well") == 0
		&& game->player.has_bucket && !game->player.has_water)
	{
		show_temp_message(game, 3.0, "You filled up your bucket!");
		game->player.has_water = true;
	}
	return (true);
}
