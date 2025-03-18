/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pause.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:51:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 09:28:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	pause_game(t_game *game)
{
	if (game->state == RUNNING)
		game->state = PAUSED;
	else
		game->state = RUNNING;
	mlx_clear_window(game->mlx, game->window->ptr);
	if (game->state == PAUSED)
		draw_pause_message(game);
	return (SUCCESS);
}
