/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/28 12:55:24 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	update_npc_list(t_game *game, t_npc *npc)
{
	game->npcs = x_realloc(game, game->npcs,
			game->npc_count * sizeof(t_npc *),
			(game->npc_count + 1) * sizeof(t_npc *));
	game->npcs[game->npc_count] = npc;
	game->npc_count++;
}

void spawn_witch_kitty(t_game *game, double x, double y)
{
	static char *idle_frames[] = {
		WS0, WS1, WS2, WS3, WS4, WS5, WS6,
		WS7, WS8, WS9, WS10, WS11, WS12, WS13
	};

	static char *move_frames[] = {
		WK_WAWAY0, WK_WAWAY1, WK_WAWAY2, WK_WAWAY3,
		WK_WTOW0,  WK_WTOW1,  WK_WTOW2,  WK_WTOW3,
		WK_WLEFT0, WK_WLEFT1, WK_WLEFT2, WK_WLEFT3,
		WK_WRI0,   WK_WRI1,   WK_WRI2,   WK_WRI3
	};

	t_npc *npc = x_calloc(game, 1, sizeof(t_npc));

	// NPC logic
	npc->pos.x       = x + 0.5;
	npc->pos.y       = y + 0.5;
	npc->state       = NPC_STATE_WALKING;
	npc->speed       = 1.0;
	npc->move_vec    = (t_dpoint){0, 0};

	// Patrol setup
	npc->waypoint_count = 4;
	npc->waypoints = x_calloc(game, npc->waypoint_count, sizeof(t_dpoint));
	npc->waypoints[0] = (t_dpoint){ x + 0.5, y + 0.5 };
	npc->waypoints[1] = (t_dpoint){ x + 3.5, y + 0.5 };
	npc->waypoints[2] = (t_dpoint){ x + 3.5, y + 3.5 };
	npc->waypoints[3] = (t_dpoint){ x + 0.5, y + 3.5 };
	npc->current_wp    = 1;
	npc->threshold_dist= 0.1;

	// Sprite animation setup
	npc->sprite.type = "witch_kitty";
	npc->sprite.size = (t_point){64, 64};
	npc->sprite.anim_index = 0;
	npc->sprite.anim_timer = 0.0;
	npc->sprite.idle_paths = idle_frames;
	npc->sprite.num_idle_frames = sizeof(idle_frames) / sizeof(idle_frames[0]);
	npc->sprite.move_paths = move_frames;
	npc->sprite.move_frames_count = sizeof(move_frames) / sizeof(move_frames[0]);
	init_sprite_frames_and_animation(game, &npc->sprite);
	update_npc_list(game, npc);
}

static void update_witch_kitty(t_npc *npc, double delta_time)
{
	// 1) Handle Animation (Idle vs Walking)
	if (npc->state == NPC_STATE_IDLE)
	{
		npc->sprite.anim_timer += delta_time * 1000.0;
		if (npc->sprite.anim_timer >= 200.0)
		{
			npc->sprite.anim_timer = 0.0;
			npc->sprite.anim_index = (npc->sprite.anim_index + 1) % npc->sprite.num_idle_frames;
		}
		return;
	}

	// 2) Walk Animation
	npc->sprite.anim_timer += delta_time * 1000.0;
	if (npc->sprite.anim_timer >= 200.0)
	{
		npc->sprite.anim_timer = 0.0;
		npc->sprite.anim_index = (npc->sprite.anim_index + 1) % 4;
	}

	// 3) Move Toward Current Waypoint
	t_dpoint target = npc->waypoints[npc->current_wp];
	double dx = target.x - npc->pos.x;
	double dy = target.y - npc->pos.y;
	double dist_sq = (dx * dx) + (dy * dy);

	if (dist_sq < (npc->threshold_dist * npc->threshold_dist))
	{
		npc->current_wp = (npc->current_wp + 1) % npc->waypoint_count;
		return;
	}

	double dist = sqrt(dist_sq);
	dx /= dist;
	dy /= dist;

	npc->pos.x += dx * npc->speed * delta_time;
	npc->pos.y += dy * npc->speed * delta_time;

	// 4) Save Movement Vector
	npc->move_vec.x = dx;
	npc->move_vec.y = dy;
}

void update_all_npcs(t_game *game, double delta_time)
{
	int i = 0;
	while (i < game->npc_count)
	{
		t_npc *npc = game->npcs[i];
		if (ft_strcmp(npc->sprite.type, "witch_kitty") == 0)
			update_witch_kitty(npc, delta_time);
		i++;
	}
}

static void sort_npcs(t_game *game, t_player player, t_npc **npcs)
{
	int		i;
	int		j;
	double	dist_i;
	double	dist_j;

	i = 0;
	while (i < game->npc_count - 1)
	{
		j = 0;
		while (j < game->npc_count - i - 1)
		{
			dist_i = (npcs[j]->pos.x - player.pos.x) * (npcs[j]->pos.x - player.pos.x)
				+ (npcs[j]->pos.y - player.pos.y) * (npcs[j]->pos.y - player.pos.y);
			dist_j = (npcs[j + 1]->pos.x - player.pos.x) * (npcs[j + 1]->pos.x - player.pos.x)
				+ (npcs[j + 1]->pos.y - player.pos.y) * (npcs[j + 1]->pos.y - player.pos.y);
			if (dist_i < dist_j)
				ft_swap(&npcs[j], &npcs[j + 1], sizeof(t_npc *));
			j++;
		}
		i++;
	}
}

static int get_walk_block(t_npc *npc, t_player *player)
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

void draw_witch_kitty(t_game *game, t_npc *npc, double *z_buffer)
{
	t_texture *tex = NULL;
	int index;

	if (npc->state == NPC_STATE_IDLE)
	{
		index = npc->sprite.anim_index;
		if (index < 0 || index >= npc->sprite.num_idle_frames)
			index = 0;
		tex = &npc->sprite.idle_frames[index];
	}
	else
	{
		// Determine Walk Animation Block (Away, Toward, Left, Right)
		int block = get_walk_block(npc, &game->player);

		int base_index = 0;
		if (block == WALK_AWAY)
			base_index = 0;
		else if (block == WALK_TOWARD)
			base_index = 4;
		else if (block == WALK_LEFT)
			base_index = 8;
		else
			base_index = 12;

		index = base_index + npc->sprite.anim_index;
		if (index < 0 || index >= npc->sprite.move_frames_count)
			index = 0;

		tex = &npc->sprite.move_frames[index];
	}

	// Create Temp Sprite for Drawing
	t_sprite temp;
	ft_bzero(&temp, sizeof(t_sprite));
	temp.pos = npc->pos;
	temp.size = npc->sprite.size;
	temp.num_idle_frames = 1;
	temp.idle_frames = tex;
	temp.type = npc->sprite.type;

	draw_sprite(game, game->player, &temp, z_buffer);
}

void draw_npcs(t_game *game, t_player player, double *z_buffer)
{
	int i;

	sort_npcs(game, player, game->npcs);
	i = 0;
	while (i < game->npc_count)
	{
		t_npc *npc = game->npcs[i];

		if (ft_strcmp(npc->sprite.type, "witch_kitty") == 0)
			draw_witch_kitty(game, npc, z_buffer);
		i++;
	}
}
