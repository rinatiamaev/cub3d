/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_win_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:17:25 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/21 13:12:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_win_message(t_game *game)
{
	int		i;
	t_point	pos;
	bool	any_saved;

	pos.y = game->window->size.y / 2;
	pos.x = game->window->size.x / 2 - 60;
	mlx_clear_window(game->mlx, game->window->ptr);
	mlx_string_put
		(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
			"CONGRATULATIONS, YOU WON!");
	pos.y += 30;
	any_saved = false;
	i = 0;
	while (i < game->npc_count)
	{
		if (game->npcs[i]->is_saved)
		{
			any_saved = true;
			mlx_string_put
				(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
					game->npcs[i]->name);
			pos.y += 20;
		}
		i++;
	}
	if (any_saved)
		mlx_string_put
			(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
				"have been saved from the labyrinth!");
	else
		mlx_string_put
			(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
				"But you locked the kittens forever...");
	mlx_string_put
		(game->mlx, game->window->ptr, 20, 20, 0xFFFFFF,
			"Press 'ESC' to exit the game");
}

