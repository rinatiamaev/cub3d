/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:05:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:15:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sprite(t_game *game, t_player player, t_sprite *sprite,
															double *z_buffer)
{
	t_sprite_draw	data;

	if (!init_sprite_draw_data(&data, player, sprite))
		return ;
	data.stripe_x = data.draw_start.x;
	while (data.stripe_x < data.draw_end.x)
	{
		draw_sprite_column(game, &data, z_buffer);
		data.stripe_x++;
	}
}
