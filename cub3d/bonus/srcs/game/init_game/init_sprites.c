/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:54:26 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/26 00:16:04 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void update_sprites_list(t_game *game, t_sprite *sprite)
{
	game->sprites = x_realloc(game, game->sprites,
			game->sprite_count * sizeof(t_sprite *),
			(game->sprite_count + 1) * sizeof(t_sprite *));
	game->sprites[game->sprite_count] = sprite;
	game->sprite_count++;
}

static void	init_sprite_frames_and_animation(t_game *game, t_sprite *sprite)
{
	struct timeval	tv;
	int				i;
	
	load_sprite_frames(game, sprite);
	i = 0;
	while (i < sprite->num_frames)
		sprite->idle_frames[i++].size = sprite->size;
	gettimeofday(&tv, NULL);
	sprite->anim_start = tv.tv_sec * 1000000L + tv.tv_usec;
}

void spawn_witch_kitty(t_game *game, double x, double y)
{
	t_sprite *sprite;
	static char *frames[] = {
		WS0, WS1, WS2, WS3, WS4, WS5, WS6, WS7, WS8, WS9, WS10, WS11, WS12, WS13
	};

	sprite = x_calloc(game, 1, sizeof(t_sprite));
	*sprite = (t_sprite){
		.pos = (t_dpoint){x + 0.5, y + 0.5},
		.type = "witch_kitty",
		.paths = frames,
		.num_frames = sizeof(frames) / sizeof(frames[0]),
		.size = (t_point){64, 64}
	};
	init_sprite_frames_and_animation(game, sprite);
	update_sprites_list(game, sprite);
}

void spawn_well(t_game *game, double x, double y)
{
	t_sprite *sprite;
	static char *frames[] = {
		IO
	};

	sprite = x_calloc(game, 1, sizeof(t_sprite));
	*sprite = (t_sprite){
		.pos = (t_dpoint){x + 0.5, y + 0.5},
		.type = "well",
		.paths = frames,
		.num_frames = sizeof(frames) / sizeof(frames[0]),
		.size = (t_point){128, 128}
	};
	init_sprite_frames_and_animation(game, sprite);
	update_sprites_list(game, sprite);
}
