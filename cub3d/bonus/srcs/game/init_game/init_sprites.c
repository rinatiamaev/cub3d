/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:13:32 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/27 00:04:56 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_sprites_list(t_game *game, t_sprite *sprite)
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
	while (i < sprite->num_idle_frames)
		sprite->idle_frames[i++].size = sprite->size;
	i = 0;
	if (sprite->move_frames)
	{
		while (i < sprite->move_frames_count)
			sprite->move_frames[i++].size = sprite->size;
	}
	gettimeofday(&tv, NULL);
	sprite->anim_start = tv.tv_sec * 1000000L + tv.tv_usec;
}

void	spawn_witch_kitty(t_game *game, double x, double y)
{
	t_sprite	*sprite;
	static char	*idle_frames[] = {
		WS0, WS1, WS2, WS3, WS4, WS5, WS6, WS7, WS8, WS9, WS10, WS11, WS12, WS13
	};
	static char	*move_frames[] = {
		WK_S0, WK_S1, WK_S2, WK_S3, WK_N0, WK_N1, WK_N2, WK_N3, WK_W0, WK_W1, WK_W2, WK_W3, WK_E0, WK_E1, WK_E2, WK_E3
	};

	sprite = x_calloc(game, 1, sizeof(t_sprite));
	*sprite = (t_sprite){
		.type = "witch_kitty",
		.pos = (t_dpoint){x + 0.5, y + 0.5},
		.size = (t_point){64, 64},
		.state = NPC_STATE_WALKING,
		.anim_index = 0,
		.anim_timer = 0,
		.idle_paths = idle_frames,
		.num_idle_frames = sizeof(idle_frames) / sizeof(idle_frames[0]),
		.move_paths = move_frames,
		.move_frames_count = sizeof(move_frames) / sizeof(move_frames[0]),
		.move_dir = 2,
		.speed = 1.0
	};
	init_sprite_frames_and_animation(game, sprite);
	update_sprites_list(game, sprite);
}

static void update_witch_kitty(t_game *game, t_sprite *kitty, double delta_time)
{
	// 1) Accumulate time
	kitty->anim_timer += delta_time * 1000.0; // convert sec -> ms, if you want

	// 2) If enough time passed, advance the anim_index
	if (kitty->anim_timer >= 200.0)  // e.g. 150ms per frame
	{
		kitty->anim_timer = 0.0;
		kitty->anim_index++;

		// If IDLE: cycle within [0..(num_idle_frames - 1)]
		if (kitty->state == NPC_STATE_IDLE)
		{
			if (kitty->anim_index >= kitty->num_idle_frames)
				kitty->anim_index = 0;
		}
		else // NPC_STATE_WALKING
		{
			// We have 4 frames per direction. So anim_index cycles 0..3
			// Then we'll compute the actual index in the 16 array at draw time
			if (kitty->anim_index >= 4)
				kitty->anim_index = 0;
		}
	}
	if (kitty->state == NPC_STATE_WALKING)
    {
        double dx = 0.0;
        double dy = 0.0;

        // move_dir: 0 => South, 1 => North, 2 => West, 3 => East
        if (kitty->move_dir == 0)      // south
            dy = 1.0;
        else if (kitty->move_dir == 1) // north
            dy = -1.0;
        else if (kitty->move_dir == 2) // west
            dx = -1.0;
        else if (kitty->move_dir == 3) // east
            dx = 1.0;

		double next_x = kitty->pos.x + dx * kitty->speed * delta_time;
		double next_y = kitty->pos.y + dy * kitty->speed * delta_time;
			
		if (can_move(game, next_x, next_y))
		{
			kitty->pos.x = next_x;
			kitty->pos.y = next_y;
		}
    }
}

void update_all_sprites(t_game *game, double delta_time)
{
    int i;

    i = 0;
    while (i < game->sprite_count)
    {
        t_sprite *spr = game->sprites[i];
        if (ft_strcmp(spr->type, "witch_kitty") == 0)
            update_witch_kitty(game, spr, delta_time);
        i++;
    }
}

void	spawn_well(t_game *game, double x, double y)
{
	t_sprite	*sprite;
	static char	*frames[] = {
		IO
	};

	sprite = x_calloc(game, 1, sizeof(t_sprite));
	*sprite = (t_sprite){
		.pos = (t_dpoint){x + 0.5, y + 0.5},
		.type = "well",
		.idle_paths = frames,
		.num_idle_frames = sizeof(frames) / sizeof(frames[0]),
		.size = (t_point){128, 128}
	};
	init_sprite_frames_and_animation(game, sprite);
	update_sprites_list(game, sprite);
}
