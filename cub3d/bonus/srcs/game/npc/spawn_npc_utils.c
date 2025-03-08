/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_npc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:26:00 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/08 21:50:06 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_sprite_frames_and_animation(t_game *game, t_sprite *sprite)
{
	struct timeval	tv;
	int				i;

	load_sprite_frames(game, sprite);
	i = 0;
	if (sprite->idle_frames)
	{
		while (i < sprite->num_idle_frames)
			sprite->idle_frames[i++].size = sprite->size;
	}
	i = 0;
	if (sprite->move_frames)
	{
		while (i < sprite->move_frames_count)
			sprite->move_frames[i++].size = sprite->size;
	}
	i = 0;
	if (sprite->speak_frames)
	{
		while (i < sprite->speak_frames_count)
			sprite->speak_frames[i++].size = sprite->size;
	}
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
