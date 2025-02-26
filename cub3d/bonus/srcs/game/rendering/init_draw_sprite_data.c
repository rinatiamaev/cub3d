/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_draw_sprite_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:18:50 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/26 23:50:13 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	compute_relative_position(t_sprite_draw *data, t_player player,
															t_sprite *sprite)
{
	data->relative_position.x = sprite->pos.x - player.pos.x;
	data->relative_position.y = sprite->pos.y - player.pos.y;
}

static bool	compute_transform(t_sprite_draw *data, t_player player)
{
	data->inverse_determinant = 1.0
		/ (player.plane.x * player.dir.y - player.dir.x * player.plane.y);
	data->transform_x
		= data->inverse_determinant * (player.dir.y * data->relative_position.x
			- player.dir.x * data->relative_position.y);
	data->transform_y
		= data->inverse_determinant
		* ((-player.plane.y) * data->relative_position.x
			+ player.plane.x * data->relative_position.y);
	if (data->transform_y <= 0.001)
		return (false);
	return (true);
}

static bool	compute_draw_dims(t_sprite_draw *data)
{
	data->screen_x = (int)(
			(WIN_W / 2.0) * (1.0 + data->transform_x / data->transform_y));
	data->height = (int)fabs((double)(WIN_H / data->transform_y));
	if (data->height == 0)
		data->height = 1;
	data->draw_start.y = -data->height / 2 + WIN_H / 2;
	if (data->draw_start.y < 0)
		data->draw_start.y = 0;
	data->draw_end.y = data->height / 2 + WIN_H / 2;
	if (data->draw_end.y >= WIN_H)
		data->draw_end.y = WIN_H - 1;
	data->width = data->height;
	data->draw_start.x = -data->width / 2 + data->screen_x;
	if (data->draw_start.x < 0)
		data->draw_start.x = 0;
	data->draw_end.x = data->width / 2 + data->screen_x;
	if (data->draw_end.x >= WIN_W)
		data->draw_end.x = WIN_W - 1;
	if (data->draw_start.x > data->draw_end.x
		|| data->draw_start.y > data->draw_end.y)
		return (false);
	return (true);
}

static void	select_texture_frame(t_sprite_draw *data, t_sprite *sprite)
{
	data->current_frame = get_current_frame(
			sprite->anim_start,
			sprite->num_idle_frames,
			200);
	data->texture = &sprite->idle_frames[data->current_frame];
	data->texture_size.x = data->texture->size.x;
	data->texture_size.y = data->texture->size.y;
}

bool	init_sprite_draw_data(t_sprite_draw *data, t_player player,
															t_sprite *sprite)
{
	compute_relative_position(data, player, sprite);
	if (!compute_transform(data, player))
		return (false);
	if (!compute_draw_dims(data))
		return (false);
	select_texture_frame(data, sprite);
	return (true);
}
