/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 22:07:05 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Allocates and initializes a new map structure.
 *
 * This function allocates memory for a new map and sets initial configuration
 * values such as uninitialized floor and ceiling colors (set to -1). It also
 * stores the provided filename in the map structure.
 *
 * @param game Pointer to the game state (used for memory allocation).
 * @param filename The name of the map file to load.
 * @return Pointer to the newly allocated and initialized map structure.
 */
static t_map	*init_map(t_game *game, char *filename)
{
	t_map	*map;

	map = x_calloc(game, 1, sizeof(t_map));
	map->filename = filename;
	map->conf.floor_color = -1;
	map->conf.ceiling_color = -1;
	return (map);
}

/**
 * @brief Creates and initializes the game window.
 *
 * Sets the window's title and dimensions based on defined constants, then
 * creates a new window using MiniLibX. If window creation fails, the function
 * triggers an error.
 *
 * @param game Pointer to the game state (provides MLX context
 *             and error handling).
 * @param window Pointer to the window structure to initialize.
 */
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

/**
 * @brief Initializes the complete game state.
 *
 * This function allocates and sets up the game structure, including:
 * - Initializing the MiniLibX context.
 * - Loading the map from the specified filename and parsing its contents.
 * - Creating the game window.
 * - Loading game textures from the map configuration.
 * - Initializing the player and the static background.
 *
 * Finally, the game state is set to RUNNING and the fully prepared game
 * structure is returned.
 *
 * @param filename The map file name to load.
 * @return Pointer to the fully initialized game state.
 */
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
