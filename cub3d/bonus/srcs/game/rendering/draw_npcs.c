/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:28:02 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 20:50:09 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_npc_dialogue(t_game *game)
{
	int		x;
	int		y;
	int		color;
	int		i;
	t_npc	*npc;

	x = (WIN_W / 2 - 128);
	y = (WIN_H - (WIN_H / 5));
	color = 0x141B1B;
	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (npc->state == NPC_STATE_SPEAK)
		{
			mlx_put_image_to_window(game->mlx, game->window->ptr,
				game->tex.dialogue_box.ptr, x, y);
			mlx_string_put(game->mlx, game->window->ptr, x + 15, y + 35, color,
				npc->lines[npc->current_line]);
		}
		i++;
	}
}

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
