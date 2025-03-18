/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_well.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 10:58:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_well(t_game *game, t_item *item, t_dpoint pos)
{
	item->type = "static";
	item->name = "well";
	item->pos = (t_dpoint){pos.x + 0.5, pos.y + 0.5};
	load_single_xpm(game, &item->texture, WELL_TEX, game->mlx);
}

void	spawn_well(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x, y};
	init_well(game, item, pos);
	update_item_list(game, item);
}
