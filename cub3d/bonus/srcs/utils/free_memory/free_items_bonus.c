/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_items_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:40:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:10:40 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Frees the memory and resources associated with a single item.
 *
 * This function handles both static and animated items. It frees the
 * texture(s) depending on the item type and then deallocates the item itself.
 *
 * @param game Pointer to the game context.
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
