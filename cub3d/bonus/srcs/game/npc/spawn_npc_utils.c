/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_npc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:26:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 14:11:10 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	set_frame_sizes(t_texture *frames, int count, t_point size)
{
	int	i;

	if (!frames)
		return ;
	i = 0;
	while (i < count)
		frames[i++].size = size;
}

void	init_sprite_frames_and_animation(t_game *game, t_sprite *sprite)
{
	struct timeval	tv;

	load_sprite_frames(game, sprite);
	set_frame_sizes
		(sprite->idle_frames, sprite->num_idle_frames, sprite->size);
	set_frame_sizes
		(sprite->move_frames, sprite->move_frames_count, sprite->size);
	set_frame_sizes
		(sprite->speak_frames, sprite->speak_frames_count, sprite->size);
	if (sprite->hit_frames)
		set_frame_sizes
			(sprite->hit_frames, sprite->hit_frames_count, sprite->size);
	gettimeofday(&tv, NULL);
	sprite->anim_start = tv.tv_sec * 1000000L + tv.tv_usec;
}

void	update_npc_list(t_game *game, t_npc *npc)
{
	game->npcs = x_realloc(game, game->npcs,
			game->npc_count * sizeof(t_npc *),
			(game->npc_count + 1) * sizeof(t_npc *));
	game->npcs[game->npc_count] = npc;
	game->npc_count++;
}

void allocate_dialogues(t_game *game, t_dial *dialog, char *dialogues[][11], int phase_count)
{
	int i = 0;

	dialog->dialogues = x_malloc(game, phase_count * sizeof(char **));
	dialog->dialogue_count = x_malloc(game, phase_count * sizeof(int));
	while (i < phase_count)
	{
		int count = 0;
		while (dialogues[i][count])
			count++;
		dialog->dialogues[i] = x_malloc(game, (count + 1) * sizeof(char *));
		if (!dialog->dialogues[i])
			return;
		dialog->dialogue_count[i] = count;
		int j = 0;
		while (j < count)
		{
			dialog->dialogues[i][j] = x_strdup(game, dialogues[i][j]);
			j++;
		}
		dialog->dialogues[i][count] = NULL;
		i++;
	}
}


