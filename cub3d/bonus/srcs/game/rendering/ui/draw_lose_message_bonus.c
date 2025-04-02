/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lose_message_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:17:25 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 20:44:10 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Displays the "You Lose" screen with a game over message.
 *
 * This function clears the game window and displays a centered "YOU LOSE"
 * message along with additional context ("the fireball got you!") and a
 * prompt to exit the game.
 *
 * All text is rendered using `mlx_string_put`, with white color and fixed
 * screen positions. The text is centered relative to the window size.
 *
 * @param game Pointer to the game state (provides window, rendering context).
 */
void	draw_lose_message(t_game *game)
{
	t_point	pos;

	pos.x = game->window->size.x >> 1;
	pos.y = game->window->size.y >> 1;
	mlx_clear_window(game->mlx, game->window->ptr);
	mlx_string_put
		(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
			"YOU LOSE");
	mlx_string_put
		(game->mlx, game->window->ptr, pos.x + 20, pos.y + 20, 0xFFFFFF,
			"the fireball got you!");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 20, 0xFFFFFF,
			"Press 'ESC' to exit the game");
}
