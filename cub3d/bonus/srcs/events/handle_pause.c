/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pause.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:51:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 14:39:38 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_pause_message(t_game *game)
{
	t_point	pos;

	pos.x = game->window->size.x / 2;
	pos.y = game->window->size.y / 2;
	mlx_string_put
		(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF, "PAUSED");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 20, 0xFFFFFF,
			"Press 'SPACE' to pause/unpause the game");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 40, 0xFFFFFF,
			"Press 'ESC' to exit the game");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 60, 0xFFFFFF,
			"Press 'WASD' to move the player");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 80, 0xFFFFFF,
			"Press '<-' or '->' to rotate the view");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 100, 0xFFFFFF,
			"Press 'E' to interact with game elements");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 120, 0xFFFFFF,
			"Press 'F' for the npc to follow you");
	
}

int	pause_game(t_game *game)
{
	game->is_paused = !game->is_paused;
	mlx_clear_window(game->mlx, game->window->ptr);
	if (game->is_paused)
		draw_pause_message(game);
	return (SUCCESS);
}
