/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_npcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:30:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/08 23:27:00 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_npc_waypoints(t_npc *npc)
{
	if (npc->waypoints)
	{
		free(npc->waypoints);
		npc->waypoints = NULL;
	}
}

static void	free_npc_textures(t_game *game, t_sprite *sprite)
{
	int	j;

	j = 0;
	while (j < sprite->num_idle_frames)
	{
		if (sprite->idle_frames[j].ptr)
			mlx_destroy_image(game->mlx, sprite->idle_frames[j].ptr);
		j++;
	}
	free(sprite->idle_frames);
	j = 0;
	while (j < sprite->move_frames_count)
	{
		if (sprite->move_frames[j].ptr)
			mlx_destroy_image(game->mlx, sprite->move_frames[j].ptr);
		j++;
	}
	free(sprite->move_frames);
	j = 0;
	while (j < sprite->speak_frames_count)
	{
		if (sprite->speak_frames[j].ptr)
			mlx_destroy_image(game->mlx, sprite->speak_frames[j].ptr);
		j++;
	}
	free(sprite->speak_frames);
}

static void	free_single_npc(t_game *game, t_npc *npc)
{
	if (!npc)
		return ;
	free_npc_waypoints(npc);
	free_npc_textures(game, &npc->sprite);
	if (npc->path)
	{
		free(npc->path);
		npc->path = NULL;
	}
	if (npc->astar)
	{
		reset_astar_struct(game, npc->astar);
		free(npc->astar);
	}
	free(npc);
}

void	free_npcs(t_game *game)
{
	int	i;

	if (!game->npcs || game->npc_count == 0)
		return ;
	i = 0;
	while (i < game->npc_count)
	{
		free_single_npc(game, game->npcs[i]);
		i++;
	}
	free(game->npcs);
}
