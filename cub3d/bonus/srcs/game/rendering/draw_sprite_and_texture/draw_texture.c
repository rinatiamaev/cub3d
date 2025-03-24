/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:45 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:15:36 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	init_texture_as_sprite(t_sprite_draw *data, t_player player,
									t_texture *texture, t_dpoint texture_pos)
{
	t_sprite	temp_sprite;

	temp_sprite.pos = texture_pos;
	temp_sprite.anim_start = 0;
	temp_sprite.idle_frames_count = 1;
	temp_sprite.idle_frames = texture;
	return (init_sprite_draw_data(data, player, &temp_sprite));
}

void	draw_texture(t_game *game, t_texture *texture,
										t_dpoint texture_pos, double *z_buffer)
{
	t_sprite_draw	data;

	if (!init_texture_as_sprite(&data, game->player, texture, texture_pos))
		return ;
	data.stripe_x = data.draw_start.x;
	while (data.stripe_x < data.draw_end.x)
	{
		draw_sprite_column(game, &data, z_buffer);
		data.stripe_x++;
	}
}
