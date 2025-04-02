/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 01:56:11 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 02:43:31 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_fps(t_game *game, double delta_time)
{
	game->frame_count++;
	game->fps_time_acc += delta_time;
	if (game->fps_time_acc >= 1.0)
	{
		game->fps = game->frame_count / game->fps_time_acc;
		game->frame_count = 0;
		game->fps_time_acc = 0.0;
	}
}

void	draw_fps(t_game *game)
{
	char	*fps_str;
	char	*prefix;
	char	*msg;

	fps_str = x_itoa(game, game->fps);
	prefix = x_strdup(game, "FPS: ");
	msg = x_strjoin_free(game, prefix, fps_str);
	mlx_string_put
		(game->mlx, game->window->ptr, WIN_W - 60, WIN_H - 40, 0xFFFFFF, msg);
	free(msg);
}
