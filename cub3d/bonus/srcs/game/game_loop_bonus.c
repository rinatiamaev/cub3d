/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:33:37 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:59:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Main game loop executed each frame.
 *
 * This function is called repeatedly by the graphical framework (MiniLibX)
 * to update and render the game state. It performs the following steps:
 * - Handles non-running states (WIN, GAME_OVER, PAUSED).
 * - Computes delta time for frame-based timing.
 * - Updates player input and camera rotation.
 * - Sorts entities for correct render ordering.
 * - Updates NPCs, items, doors, story state, and temporary messages.
 * - Checks for win conditions.
 * - Renders the full scene and HUD (FPS counter, dialogue, etc.).
 *
 * @param game Pointer to the game state.
 * @return Always returns 0 (used to maintain loop compatibility with MiniLibX).
 */

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
