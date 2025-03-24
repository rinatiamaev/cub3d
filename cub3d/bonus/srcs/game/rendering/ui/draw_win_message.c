/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_win_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:17:25 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:24:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_win_title(t_game *game, t_point *pos)
{
	pos->y = game->window->size.y >> 1;
	pos->x = (game->window->size.x >> 1) - 60;
	mlx_clear_window(game->mlx, game->window->ptr);
	mlx_string_put(game->mlx, game->window->ptr, pos->x, pos->y, 0xFFFFFF,
		"CONGRATULATIONS, YOU WON!");
	pos->y += 30;
}

static bool	draw_saved_npcs(t_game *game, t_point *pos)
{
	bool	any_saved;
	int		i;

	i = 0;
	any_saved = false;
	while (i < game->npc_count)
	{
		if (game->npcs[i]->is_saved)
		{
			any_saved = true;
			mlx_string_put(game->mlx, game->window->ptr, pos->x, pos->y,
				0xFFFFFF, game->npcs[i]->name);
			pos->y += 20;
		}
		i++;
	}
	return (any_saved);
}

static void	draw_outcome_message(t_game *game, t_point pos, bool any_saved)
{
	if (any_saved)
		mlx_string_put(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
			"have been saved from the labyrinth!");
	else
		mlx_string_put(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
			"But you locked the kittens forever...");
}

static void	draw_exit_instruction(t_game *game)
{
	mlx_string_put(game->mlx, game->window->ptr, 20, 20, 0xFFFFFF,
		"Press 'ESC' to exit the game");
}

void	draw_win_message(t_game *game)
{
	t_point	pos;
	bool	any_saved;

	draw_win_title(game, &pos);
	any_saved = draw_saved_npcs(game, &pos);
	draw_outcome_message(game, pos, any_saved);
	draw_exit_instruction(game);
}
