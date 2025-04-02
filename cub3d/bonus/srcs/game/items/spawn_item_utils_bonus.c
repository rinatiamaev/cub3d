/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_item_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:26:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 10:34:04 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_item_list(t_game *game, t_item *item)
{
	game->items = x_realloc(game, game->items,
			game->item_count * sizeof(t_item *),
			(game->item_count + 1) * sizeof(t_item *));
	game->items[game->item_count] = item;
	game->item_count++;
}
