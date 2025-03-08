/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:28:02 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 00:24:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void draw_npc_dialogue(t_game *game, t_npc *npc)
{
	int x, y, color;

	x = 20;
	y = 20;
	color = 0xFFFFFF;
	if (npc->is_talking && npc->lines && npc->current_line < npc->line_count)
	{
		mlx_string_put(game->mlx, game->window->ptr, x, y, color,
			npc->lines[npc->current_line]);
	}
}

void	draw_npcs(t_game *game, double *z_buffer)
{
	t_npc	*npc;
	int		i;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (ft_strcmp(npc->sprite.type, "kitty") == 0)
			draw_kitty_npc(game, npc, z_buffer);
		i++;
	}
}
