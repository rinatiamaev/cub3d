/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_splash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:13:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:22:09 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_splash_animation(t_player *player, double delta_time)
{
	const double	anim_speed_ms = 100.0;

	player->sprite.anim_timer += delta_time * 1000.0;
	if (player->sprite.anim_timer >= anim_speed_ms)
	{
		player->sprite.anim_timer -= anim_speed_ms;
		player->sprite.anim_index++;
		if (player->sprite.anim_index >= player->sprite.splash_frames_count)
		{
			player->sprite.anim_index = 0;
			player->is_splashing = false;
		}
	}
}

static t_point	get_splash_draw_position(t_texture *frame)
{
	t_point	pos;

	pos.x = (WIN_W - frame->size.x) / 2;
	pos.y = WIN_H - frame->size.y;
	return (pos);
}

static inline unsigned int	get_tex_color(t_texture *tex, int x, int y)
{
	unsigned int	*pixel_ptr;
	unsigned int	color;

	if (x < 0 || x >= tex->size.x || y < 0 || y >= tex->size.y)
		return (42);
	pixel_ptr
		= (unsigned int *)(tex->addr + y * tex->line_size + x
			* (tex->bpp >> 3));
	color = *pixel_ptr;
	if ((color & 0x00FFFFFF) == 0x000000)
		return (42);
	return (color);
}

static void	draw_splash_frame(t_game *game, t_texture *frame, t_point start)
{
	int				x;
	int				y;
	char			*dst;
	unsigned int	color;

	y = 0;
	while (y < frame->size.y)
	{
		x = 0;
		dst = game->img.addr + ((start.y + y) * game->img.line_size)
			+ (start.x * (game->img.bpp >> 3));
		while (x < frame->size.x)
		{
			color = get_tex_color(frame, x, y);
			if ((color & 0x00FFFFFF) != 42)
				*(unsigned int *)dst = color;
			dst += (game->img.bpp >> 3);
			x++;
		}
		y++;
	}
}

void	draw_splash(t_game *game, t_player *player, double delta_time)
{
	t_texture	*splash_frame;
	t_point		start;

	if (!player->is_splashing)
		return ;
	update_splash_animation(player, delta_time);
	splash_frame = &player->sprite.splash_frames[player->sprite.anim_index];
	start = get_splash_draw_position(splash_frame);
	draw_splash_frame(game, splash_frame, start);
}
