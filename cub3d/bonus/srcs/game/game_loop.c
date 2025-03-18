/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:33:37 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/17 20:25:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	game_loop(t_game *game)
{
	double	delta_time;

	if (game->state != RUNNING)
		return (0);
	delta_time = get_delta_time();
	handle_player_moves(game, delta_time);
	handle_mouse_movement(game, game->window);
	update_all_npcs(game, delta_time);
	update_doors(game, delta_time);
	update_story(game);
	render_scene(game, delta_time);
	return (0);
}
