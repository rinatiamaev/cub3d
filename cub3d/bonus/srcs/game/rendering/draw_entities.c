/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:34:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 22:10:19 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_entity	*get_entities(t_game *game)
{
	int			count;
	int			i;
	t_entity	*entities;

	count = game->npc_count + game->item_count;
	entities = x_calloc(game, count, sizeof(t_entity));
	i = -1;
	while (++i < game->npc_count)
	{
		entities[i].type = NPC;
		entities[i].pos = game->npcs[i]->pos;
		entities[i].ptr = game->npcs[i];
	}
	i = -1;
	while (++i < game->item_count)
	{
		entities[game->npc_count + i].type = ITEM;
		entities[game->npc_count + i].pos = game->items[i]->pos;
		entities[i + game->npc_count].ptr = game->items[i];
	}
	return (entities);
}

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

static void	draw_npc(t_game *game, t_npc *npc, double *z_buffer)
{
	if (ft_strcmp(npc->type, "kitty") == 0)
		draw_kitty_npc(game, npc, z_buffer);
	else if (ft_strcmp(npc->type, "fireSpirit") == 0)
		draw_fire_spirit(game, npc, z_buffer);
}

static void draw_item(t_game *game, t_item *item, double *z_buffer)
{
	if (ft_strcmp(item->name, "key") == 0)
		draw_key(game, item, z_buffer);
	else
		draw_texture(game, game->player, item, z_buffer);
}

void	draw_entities(t_game *game, double *z_buffer)
{
	t_entity	*entities;
	int			i;

	entities = get_entities(game);
	sort_entities(entities, game->npc_count + game->item_count, &game->player);
	i = -1;
	while (++i < game->npc_count + game->item_count)
	{
		if (entities[i].type == NPC)
		{
			draw_npc(game, (t_npc *)entities[i].ptr, z_buffer);
		}
		else if (entities[i].type == ITEM)
		{
			draw_item(game, (t_item *)entities[i].ptr, z_buffer);
		}
	}
	free(entities);
}
