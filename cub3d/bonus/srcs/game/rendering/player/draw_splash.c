/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_splash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:13:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 13:03:30 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	play_splash_animation(t_player *player, double delta_time)
{
	double	anim_speed;

	anim_speed = 100.0;
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

void	draw_splash(t_game *game, t_player *player, double delta_time)
{
	int			x;
	int			y;
	t_point		start;
	t_texture	*splash_frame;
	int			color;

	if (!player->is_splashing)
		return ;
	play_splash_animation(player, delta_time);
	splash_frame = &player->sprite.splash_frames[player->sprite.anim_index];
	start.x = (WIN_W - splash_frame->size.x) / 2;
	start.y = WIN_H - splash_frame->size.y;
	y = -1;
	while (++y < splash_frame->size.y)
	{
		x = -1;
		while (++x < splash_frame->size.x)
		{
			color = get_tex_color(splash_frame, x, y);
			if (color != 42 && (color & 0x00FFFFFF) != 0x000000)
				put_pixel(&game->img, start.x + x, start.y + y, color);
		}
	}
}
