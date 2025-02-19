/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 15:10:58 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	init_player(t_player *player)
{
	player->pos = (t_dpoint){player->pos.x + 0.5, player->pos.y + 0.5};
	player->dir = (t_dpoint){0, 0};
	player->plane = (t_dpoint){0, 0};
	player->rot_speed = 0.05;
	player->move_speed = 0.05;
	if (player->conf_dir == 'N')
	{
		player->dir = (t_dpoint){0.0, -1.0};
		player->plane = (t_dpoint){0.66, 0.0};
	}
	else if (player->conf_dir == 'S')
	{
		player->dir = (t_dpoint){0.0, 1.0};
		player->plane = (t_dpoint){-0.66, 0.0};
	}
	else if (player->conf_dir == 'W')
	{
		player->dir = (t_dpoint){-1.0, 0.0};
		player->plane = (t_dpoint){0.0, -0.66};
	}
	else if (player->conf_dir == 'E')
	{
		player->dir = (t_dpoint){1.0, 0.0};
		player->plane = (t_dpoint){0.0, 0.66};
	}
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
	load_textures(game, game->map->conf);
	init_player(&game->player);
	game->is_paused = false;
	return (game);
}
