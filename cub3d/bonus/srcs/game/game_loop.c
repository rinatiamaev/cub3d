/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:33:37 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/08 23:32:06 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	get_delta_time(void)
{
	static struct timeval	prev_time;
	struct timeval			current_time;
	double					delta_time;

	gettimeofday(&current_time, NULL);
	if (prev_time.tv_sec == 0 && prev_time.tv_usec == 0)
	{
		prev_time = current_time;
		return (0.0);
	}
	delta_time = (current_time.tv_sec - prev_time.tv_sec)
		+ (current_time.tv_usec - prev_time.tv_usec) / 1000000.0;
	prev_time = current_time;
	return (delta_time);
}

int	game_loop(t_game *game)
{
	double	delta_time;

	if (game->is_paused)
		return (0);
	delta_time = get_delta_time();
	handle_player_moves(game);
	handle_mouse_movement(game, game->window);
	update_all_npcs(game, delta_time);
	update_doors(game, delta_time);
	render_scene(game);
	return (0);
}
