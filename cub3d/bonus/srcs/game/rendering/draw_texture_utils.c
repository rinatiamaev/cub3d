/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:22:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 13:06:56 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	compute_item_relative_position(t_sprite_draw *data,
												t_player player, t_item *item)
{
	data->relative_position.x = item->pos.x - player.pos.x;
	data->relative_position.y = item->pos.y - player.pos.y;
}

static bool	compute_item_transform(t_sprite_draw *data, t_player player)
{
	data->inverse_determinant = 1.0
		/ (player.plane.x * player.dir.y - player.dir.x * player.plane.y);
	data->transform_x = data->inverse_determinant
		* (player.dir.y * data->relative_position.x
			- player.dir.x * data->relative_position.y);
	data->transform_y = data->inverse_determinant
		* (-player.plane.y * data->relative_position.x
			+ player.plane.x * data->relative_position.y);
	return (data->transform_y > 0.001);
}

static bool	compute_item_draw_dimensions(t_sprite_draw *data)
{
	data->screen_x = (int)((WIN_W / 2.0)
			* (1.0 + data->transform_x / data->transform_y));
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
	return (!(data->draw_start.x > data->draw_end.x
			|| data->draw_start.y > data->draw_end.y));
}

static void	set_item_texture(t_sprite_draw *data, t_item *item)
{
	data->texture = &item->texture;
	data->texture_size = item->texture.size;
}

bool	init_texture_draw_data(t_sprite_draw *data,
									t_player player, t_item *item)
{
	compute_item_relative_position(data, player, item);
	if (!compute_item_transform(data, player))
		return (false);
	if (!compute_item_draw_dimensions(data))
		return (false);
	set_item_texture(data, item);
	return (true);
}
