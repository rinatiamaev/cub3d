/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:33:37 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/28 12:31:32 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int game_loop(t_game *game)
{
	static struct timeval prev_time = {0, 0};
	struct timeval        current_time;
	double               delta_time;

	gettimeofday(&current_time, NULL);
	if (prev_time.tv_sec == 0 && prev_time.tv_usec == 0)
		prev_time = current_time;
	double elapsed = (current_time.tv_sec - prev_time.tv_sec) 
				+ (current_time.tv_usec - prev_time.tv_usec) / 1000000.0;
	delta_time = elapsed;
	prev_time = current_time;
	handle_player_moves(game);
	handle_mouse_movement(game, game->window);
	update_all_npcs(game, delta_time);
	render_scene(game);
	return (0);
}
