/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 01:56:11 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 22:03:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Updates the FPS (frames per second) counter.
 *
 * Accumulates the number of frames and the elapsed time to compute the
 * current FPS once per second. Resets the counters after each update.
 *
 * This function should be called once per frame.
 *
 * @param game Pointer to the game state.
 */
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

/**
 * @brief Draws the current FPS counter on the screen.
 *
 * Converts the FPS value to a string and displays it in the bottom-right
 * corner of the game window using MiniLibX. Uses custom memory-safe
 * string functions.
 *
 * @param game Pointer to the game state.
 */
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
