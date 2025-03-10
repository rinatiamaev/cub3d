/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:51:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 01:03:22 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_pause_message(t_game *game)
{
	t_point	pos;

	pos.x = game->window->size.x / 2;
	pos.y = game->window->size.y / 2;
	mlx_string_put(game->mlx, game->window->ptr, pos.x, pos.y,
		0xFFFFFF, "PAUSED");
}

int	pause_game(t_game *game)
{
	game->is_paused = !game->is_paused;
	mlx_clear_window(game->mlx, game->window->ptr);
	if (game->is_paused)
		draw_pause_message(game);
	return (SUCCESS);
}
