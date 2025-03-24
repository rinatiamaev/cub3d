/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entities_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:38:38 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:14:06 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	sort_entities(t_entity *entities, int count, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (ft_cab_dist_dpoint(entities[j].pos, player->pos)
				< ft_cab_dist_dpoint(entities[j + 1].pos, player->pos))
				ft_swap(&entities[j], &entities[j + 1], sizeof(t_entity));
		}
	}
}

void	update_entities_sort(t_game *game)
{
	int	i;

	if (game->entities)
		free(game->entities);
	game->entity_count = game->npc_count + game->item_count;
	game->entities = x_calloc(game, game->entity_count, sizeof(t_entity));
	i = -1;
	while (++i < game->npc_count)
	{
		game->entities[i].type = NPC;
		game->entities[i].pos = game->npcs[i]->pos;
		game->entities[i].ptr = game->npcs[i];
	}
	i = -1;
	while (++i < game->item_count)
	{
		game->entities[game->npc_count + i].type = ITEM;
		game->entities[game->npc_count + i].pos = game->items[i]->pos;
		game->entities[game->npc_count + i].ptr = game->items[i];
	}
	sort_entities(game->entities, game->entity_count, &game->player);
}
