/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:38:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/17 20:51:53 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	play_splash_animation(t_player *player, double delta_time)
{
	const double anim_speed = 200.0;

	player->sprite.anim_timer += delta_time * 1000.0;
	if (player->sprite.anim_timer >= anim_speed)
	{
		player->sprite.anim_timer -= anim_speed;
		player->sprite.anim_index++;
		if (player->sprite.anim_index >= player->sprite.splash_frames_count)
		{
			player->sprite.anim_index = 0;
			player->is_splashing = false;
		}
	}
}

void draw_player(t_game *game, t_player *player, double delta_time)
{
	if (player->is_splashing)
	{
		play_splash_animation(player, delta_time);
		mlx_put_image_to_window(game->mlx, game->window->ptr,
			player->sprite.splash_frames[player->sprite.anim_index].ptr, 0, 0);
	}
}


static void	init_player_sprite_and_animation(t_game *game, t_player *player, t_sprite *sprite)
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
	init_player_sprite_and_animation(game, player, &player->sprite);
}
