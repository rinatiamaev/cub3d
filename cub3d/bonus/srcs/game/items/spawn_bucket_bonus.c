/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bucket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:00:12 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 13:02:08 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_bucket(t_game *game, t_item *item, t_dpoint pos)
{
	item->type = "static";
	item->name = "bucket";
	item->is_collectible = true;
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, BUCKET_TEX, game->mlx);
}

void	spawn_bucket(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	init_bucket(game, item, pos);
	update_item_list(game, item);
}
