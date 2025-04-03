/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pause_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:51:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:46:25 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Toggles the game state between PAUSED and RUNNING.
 *
 * If the game is currently running, it pauses it and draws the pause message.
 * If the game is paused, it resumes the game. Does nothing if the game is
 * over. The window is cleared before rendering the pause screen if needed.
 *
 * @param game Pointer to the game structure.
 * @return Always returns SUCCESS.
 */
int	pause_game(t_game *game)
{
	if (game->state == GAME_OVER)
		return (SUCCESS);
	if (game->state == RUNNING)
		game->state = PAUSED;
	else
		game->state = RUNNING;
	mlx_clear_window(game->mlx, game->window->ptr);
	if (game->state == PAUSED)
		draw_pause_message(game);
	return (SUCCESS);
}
