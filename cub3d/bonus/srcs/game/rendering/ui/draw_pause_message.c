/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pause_message.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:27:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:26:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_pause_message(t_game *game)
{
	t_point	pos;

	pos = (t_point){game->window->size.x >> 1, game->window->size.y >> 1};
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
			"Press 'WASD' to move the player,'<-' or '->' to rotate the view");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 100, 0xFFFFFF,
			"Press 'E' to interact with game elements");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 120, 0xFFFFFF,
			"Press 'F' for the npc to follow you when relevant");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 140, 0xFFFFFF,
			"Press 'M' yo display the minimap");
}
