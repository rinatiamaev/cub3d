/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:28:02 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 16:03:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	sort_npcs(t_game *game, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->npc_count - 1)
	{
		j = 0;
		while (j < game->npc_count - i - 1)
		{
			if (ft_cab_dist_dpoint(game->npcs[j]->pos, player->pos)
				< ft_cab_dist_dpoint(game->npcs[j + 1]->pos, player->pos))
				ft_swap(&game->npcs[j], &game->npcs[j + 1], sizeof(t_npc *));
			j++;
		}
		i++;
	}
}

void	draw_npcs(t_game *game, double *z_buffer)
{
	t_npc	*npc;
	int		i;

	sort_npcs(game, &game->player);
	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (ft_strcmp(npc->type, "kitty") == 0)
			draw_kitty_npc(game, npc, z_buffer);
		else if (ft_strcmp(npc->type, "fireSpirit") == 0)
			draw_fire_spirit(game, npc, z_buffer);
		i++;
	}
}
