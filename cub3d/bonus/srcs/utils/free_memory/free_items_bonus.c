/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_items_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:40:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:54:56 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Frees the memory and resources associated with a single item.
 *
 * This function handles both static and animated items. It releases
 * the associated texture using MiniLibX for static items, or calls
 * `free_tex_frames` for animated items. Finally, it deallocates the item
 * itself.
 *
 * @param game Pointer to the game context (used for texture cleanup).
 * @param item Pointer to the item to be freed.
 */
void	free_single_item(t_game *game, t_item *item)
{
	if (!item)
		return ;
	if (ft_strcmp(item->type, "static") == 0)
		mlx_destroy_image(game->mlx, item->texture.ptr);
	else if (ft_strcmp(item->type, "animated") == 0)
		free_tex_frames
			(game, item->sprite.idle_frames, item->sprite.idle_frames_count);
	free(item);
}

/**
 * @brief Frees all items currently loaded in the game.
 *
 * Iterates through the game's item list, freeing each one using
 * `free_single_item`, then deallocates the array of item pointers itself.
 *
 * @param game Pointer to the game structure containing the items array.
 */
void	free_items(t_game *game)
{
	int	i;

	if (!game->items)
		return ;
	i = 0;
	while (i < game->item_count)
	{
		free_single_item(game, game->items[i]);
		i++;
	}
	free(game->items);
}
