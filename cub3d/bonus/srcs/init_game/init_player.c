/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:38:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 10:13:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_splash_animation(t_game *game, t_player *player, t_sprite *sprite)
{
	static char *splash_frames[] = {
		SPLASH_1, SPLASH_2, SPLASH_3, SPLASH_4, SPLASH_5, SPLASH_6, SPLASH_7
	};
	player->sprite.size = (t_point){WIN_W, WIN_H};
	player->sprite.splash_paths = splash_frames;
	player->sprite.splash_frames_count
		= sizeof(splash_frames) / sizeof(char *);
	player->sprite.anim_index = 0;
	player->sprite.anim_timer = 0.0;
	load_sprite_animation(game, &sprite->splash_frames, sprite->splash_paths,
		sprite->splash_frames_count);
}

void	init_player(t_game *game, t_player *player)
{
	player->pos = (t_dpoint){player->pos.x + 0.5, player->pos.y + 0.5};
	player->rot_speed = 5;
	player->move_speed = 3;
	if (player->conf_dir == 'N')
		player->angle = 3 * M_PI / 2;
	else if (player->conf_dir == 'S')
		player->angle = M_PI / 2;
	else if (player->conf_dir == 'W')
		player->angle = M_PI;
	else if (player->conf_dir == 'E')
		player->angle = 0;
	player->dir.x = cos(player->angle);
	player->dir.y = sin(player->angle);
	player->plane.x = -sin(player->angle) * FOV;
	player->plane.y = cos(player->angle) * FOV;
	player->has_water = true;
	init_splash_animation(game, player, &player->sprite);
}
