/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/28 01:46:42 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void spawn_witch_kitty(t_game *game, double x, double y)
{
	static char *idle_frames[] = {
		WS0, WS1, WS2, WS3, WS4, WS5, WS6,
		WS7, WS8, WS9, WS10, WS11, WS12, WS13
	};

	// 0..3 => walk_away, 4..7 => walk_toward, 8..11 => walk_left, 12..15 => walk_right
	static char *move_frames[] = {
		WK_WAWAY0, WK_WAWAY1, WK_WAWAY2, WK_WAWAY3,
		WK_WTOW0,  WK_WTOW1,  WK_WTOW2,  WK_WTOW3,
		WK_WLEFT0, WK_WLEFT1, WK_WLEFT2, WK_WLEFT3,
		WK_WRI0,   WK_WRI1,   WK_WRI2,   WK_WRI3
	};

	t_sprite *sprite = x_calloc(game, 1, sizeof(t_sprite));
	sprite->type          = "witch_kitty";
	sprite->pos.x         = x + 0.5;
	sprite->pos.y         = y + 0.5;
	sprite->size.x        = 64;
	sprite->size.y        = 64;
	sprite->state         = NPC_STATE_WALKING;
	sprite->anim_index    = 0;
	sprite->anim_timer    = 0.0;
	sprite->speed         = 1.0;

	// IDLE
	sprite->idle_paths      = idle_frames;
	sprite->num_idle_frames = (int)(sizeof(idle_frames) / sizeof(idle_frames[0]));

	// MOVE
	sprite->move_paths        = move_frames;
	sprite->move_frames_count = (int)(sizeof(move_frames) / sizeof(move_frames[0]));

	// Waypoints
	sprite->waypoint_count = 4;
	sprite->waypoints = x_calloc(game, sprite->waypoint_count, sizeof(t_dpoint));
	sprite->waypoints[0] = (t_dpoint){ x + 0.5, y + 0.5 };
	sprite->waypoints[1] = (t_dpoint){ x + 3.5, y + 0.5 };
	sprite->waypoints[2] = (t_dpoint){ x + 3.5, y + 3.5 };
	sprite->waypoints[3] = (t_dpoint){ x + 0.5, y + 3.5 };
	sprite->current_wp    = 1;
	sprite->threshold_dist= 0.1;
	init_sprite_frames_and_animation(game, sprite);
	update_sprites_list(game, sprite);
}

static void update_witch_kitty(t_sprite *sprite, double delta_time)
{
	if (sprite->state == NPC_STATE_IDLE)
	{
		sprite->anim_timer += delta_time * 1000.0;
		if (sprite->anim_timer >= 200.0)
		{
			sprite->anim_timer = 0.0;
			sprite->anim_index++;
			if (sprite->anim_index >= sprite->num_idle_frames)
				sprite->anim_index = 0;
		}
		return ;
	}
	sprite->anim_timer += delta_time * 1000.0;
	if (sprite->anim_timer >= 200.0)
	{
		sprite->anim_timer = 0.0;
		// 4 frames per direction set
		sprite->anim_index = (sprite->anim_index + 1) % 4;
	}

	// 2) Move to waypoint
	t_dpoint target = sprite->waypoints[sprite->current_wp];
	double dx = target.x - sprite->pos.x;
	double dy = target.y - sprite->pos.y;
	double dist_sq = (dx * dx) + (dy * dy);

	if (dist_sq < (sprite->threshold_dist * sprite->threshold_dist))
	{
		sprite->current_wp = (sprite->current_wp + 1) % sprite->waypoint_count;
		return ;
	}

	double dist = sqrt(dist_sq);
	dx /= dist;
	dy /= dist;

	sprite->pos.x += dx * sprite->speed * delta_time;
	sprite->pos.y += dy * sprite->speed * delta_time;

	// 3) Save the movement vector in sprite->move_vec
	sprite->move_vec.x = dx;
	sprite->move_vec.y = dy;
}

static int get_walk_block(t_sprite *npc, t_player *player)
{
	// 1) Movement vector angle
	double angle_move = atan2(npc->move_vec.y, npc->move_vec.x);

	// 2) Vector from npc->pos to player->pos
	double dx = player->pos.x - npc->pos.x;
	double dy = player->pos.y - npc->pos.y;
	double angle_player = atan2(dy, dx);

	// 3) difference
	double diff = angle_move - angle_player;
	// wrap to [-pi..pi]
	while (diff < -M_PI) diff += 2 * M_PI;
	while (diff >  M_PI) diff -= 2 * M_PI;

	// convert to degrees [0..360)
	double deg = diff * (180.0 / M_PI);
	if (deg < 0)
		deg += 360.0;

	// 4) Decide block
	// We'll define these blocks:
	//  0 => AWAY   (    ~180°, around 135..225   )
	//  1 => TOWARD (    ~0°,   around 315..45    )
	//  2 => LEFT   (    ~90°,  around 45..135    )
	//  3 => RIGHT  (    ~270°, around 225..315   )
	// Tweak angle ranges to match your sprite orientation

	if ((deg >= 315 && deg < 360) || (deg >= 0 && deg < 45))
		return WALK_TOWARD;
	else if (deg >= 45 && deg < 135)
		return WALK_LEFT;
	else if (deg >= 135 && deg < 225)
		return WALK_AWAY;
	else
		return WALK_RIGHT;
}

void draw_witch_kitty(t_game *game, t_sprite *sprite, double *z_buffer)
{
	t_texture *tex = NULL;
	int        index;

	if (sprite->state == NPC_STATE_IDLE)
	{
		index = sprite->anim_index;
		if (index < 0 || index >= sprite->num_idle_frames)
			index = 0;
		tex = &sprite->idle_frames[index];
	}
	else
	{
		// We want to pick away/toward/left/right
		// and each block has 4 frames => total 16
		int block = get_walk_block(sprite, &game->player);
		// block => 0=away, 1=toward, 2=left, 3=right

		int base_index = 0;
		if (block == WALK_AWAY)
			base_index = 0;		// away => frames 0..3
		else if (block == WALK_TOWARD)
			base_index = 4;		// toward => 4..7
		else if (block == WALK_LEFT)
			base_index = 8;		// left => 8..11
		else
			base_index = 12;	// right => 12..15

		index = base_index + sprite->anim_index;
		if (index < 0 || index >= sprite->move_frames_count)
			index = 0;

		tex = &sprite->move_frames[index];
	}

	t_sprite temp;
	ft_bzero(&temp, sizeof(t_sprite));
	temp.pos = sprite->pos;
	temp.size = sprite->size;
	temp.num_idle_frames = 1;
	temp.idle_frames = tex;
	temp.type = sprite->type;

	draw_sprite(game, game->player, &temp, z_buffer);
}

void update_all_sprites(t_game *game, double delta_time)
{
	int i;

	i = 0;
	while (i < game->sprite_count)
	{
		t_sprite *spr = game->sprites[i];
		if (ft_strcmp(spr->type, "witch_kitty") == 0)
			update_witch_kitty(spr, delta_time);
		i++;
	}
}
