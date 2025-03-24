/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_temp_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:35:20 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:27:48 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_temp_message(t_game *game, double delta_time)
{
	if (game->temp_msg_visible)
	{
		game->temp_msg_timer -= delta_time;
		if (game->temp_msg_timer <= 0)
		{
			game->temp_msg_visible = false;
			game->temp_msg[0] = '\0';
		}
	}
}

void	show_temp_message(t_game *game, double duration, const char *message)
{
	ft_strlcpy(game->temp_msg, message, sizeof(game->temp_msg));
	game->temp_msg_visible = true;
	game->temp_msg_timer = duration;
}

void	draw_temp_message(t_game *game)
{
	int	x;
	int	y;
	int	color;

	if (!game->temp_msg_visible)
		return ;
	x = ((WIN_W >> 1) - 128);
	y = (WIN_H - (WIN_H / 5));
	color = 0x141B1B;
	mlx_put_image_to_window
		(game->mlx, game->window->ptr, game->tex.dialogue_box.ptr, x, y);
	mlx_string_put
		(game->mlx, game->window->ptr, x + 15, y + 35, color, game->temp_msg);
}
