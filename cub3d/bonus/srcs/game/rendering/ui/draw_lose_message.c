/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lose_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:17:25 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 01:25:33 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
