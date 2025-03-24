/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 01:45:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_map	*init_map(t_game *game, char *filename)
{
	t_map	*map;

	map = x_calloc(game, 1, sizeof(t_map));
	map->filename = filename;
	map->conf.floor_color = -1;
	map->conf.ceiling_color = -1;
	return (map);
}

static void	init_window(t_game *game, t_window *window)
{
	window->name = WIN_NAME;
	window->size = (t_point){WIN_W, WIN_H};
	window->ptr = mlx_new_window(game->mlx,
			game->window->size.x, game->window->size.y,
			game->window->name);
	if (!game->window->ptr)
		error(game, "mlx_new_window() failed");
}

t_game	*init_game(char *filename)
{
	t_game	*game;

	game = x_calloc(NULL, 1, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		error(game, "mlx_init() failed");
	game->map = init_map(game, filename);
	parse_map(game, game->map);
	game->window = x_calloc(game, 1, sizeof(t_window));
	init_window(game, game->window);
	load_game_textures(game, game->map->conf);
	init_player(game, &game->player);
	init_background(game);
	game->state = RUNNING;
	return (game);
}
