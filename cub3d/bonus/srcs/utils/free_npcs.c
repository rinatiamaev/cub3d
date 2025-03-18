/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_npcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:30:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/17 20:08:26 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_tex_frames(t_game *game, t_texture *frames, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		if (frames[j].ptr)
			mlx_destroy_image(game->mlx, frames[j].ptr);
		j++;
	}
	free(frames);
}

void	free_npc_textures(t_game *game, t_sprite *sprite)
{
	free_tex_frames(game, sprite->idle_frames, sprite->idle_frames_count);
	free_tex_frames(game, sprite->move_frames, sprite->move_frames_count);
	free_tex_frames(game, sprite->speak_frames, sprite->speak_frames_count);
	if (sprite->hit_frames)
		free_tex_frames(game, sprite->hit_frames, sprite->hit_frames_count);
}

static void	free_dialogues(t_dial *dialog)
{
	int	i;
	int	j;

	i = 0;
	while (i < dialog->phase_count)
	{
		if (dialog->dialogues[i])
		{
			j = 0;
			while (dialog->dialogues[i][j])
			{
				free(dialog->dialogues[i][j]);
				j++;
			}
			free(dialog->dialogues[i]);
		}
		i++;
	}
	free(dialog->dialogues);
	free(dialog->dialogue_count);
}

void	free_single_npc(t_game *game, t_npc *npc)
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
	free_dialogues(&npc->dialogue);
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
