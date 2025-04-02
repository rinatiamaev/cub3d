/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:33:37 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 01:56:07 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	game_loop(t_game *game)
{
	double	delta_time;

	if (!handle_game_state(game))
		return (0);
	delta_time = get_delta_time();
	update_fps(game, delta_time);
	handle_player_moves(game, delta_time);
	handle_mouse_movement(game, game->window);
	update_entities_sort(game);
	update_all_npcs(game, delta_time);
	update_items(game, delta_time);
	update_doors(game, delta_time);
	update_story(game);
	update_temp_message(game, delta_time);
	check_win_condition(game);
	render_scene(game, delta_time);
	draw_fps(game);
	return (0);
}
