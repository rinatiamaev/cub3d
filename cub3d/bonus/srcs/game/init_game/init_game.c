/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/25 22:31:03 by nlouis           ###   ########.fr       */
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

static void	init_player(t_player *player)
{
	// Center the player within the tile grid (adding 0.5 offsets).
	player->pos = (t_dpoint){player->pos.x + 0.5, player->pos.y + 0.5};

	// Set movement and rotation speed
	player->rot_speed = 5;    // Rotation speed (in degrees per frame)
	player->move_speed = 0.05; // Movement speed (units per frame)

	// Set the player's initial facing direction (angle) based on map configuration.
	if (player->conf_dir == 'N')      // Facing North
		player->angle = 3 * M_PI / 2; // Equivalent to 270 degrees
	else if (player->conf_dir == 'S') // Facing South
		player->angle = M_PI / 2;     // Equivalent to 90 degrees
	else if (player->conf_dir == 'W') // Facing West
		player->angle = M_PI;         // Equivalent to 180 degrees
	else if (player->conf_dir == 'E') // Facing East
		player->angle = 0;            // Equivalent to 0 degrees

	/*
	** PLAYER DIRECTION (`dir`):
	** - This vector represents the **player's forward movement direction**.
	** - It is calculated using trigonometry (cosine & sine of `angle`).
	** - The **X component** determines left/right movement.
	** - The **Y component** determines up/down movement.
	*/
	player->dir.x = cos(player->angle); // Forward movement in X-direction
	player->dir.y = sin(player->angle); // Forward movement in Y-direction

	/*
	** CAMERA PLANE (`plane`):
	** - This defines the **2D projection plane** perpendicular to `dir`.
	** - It controls the **field of view (FOV)**.
	** - The length of this vector affects how "wide" the player's vision is.
	** - Commonly, `plane` is set to 0.66 * perpendicular to `dir`.
	**   - 0.66 is an arbitrary FOV factor used in Wolfenstein-like engines.
	** - The plane should always be **90 degrees rotated** from `dir`, so:
	**   - If `dir` is (cos(angle), sin(angle))
	**   - Then `plane` is (-sin(angle) * 0.66, cos(angle) * 0.66)
	*/
	player->plane.x = -sin(player->angle) * FOV; // Perpendicular X to `dir`
	player->plane.y = cos(player->angle) * FOV;  // Perpendicular Y to `dir`
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
	load_walls_texture(game, game->map->conf);
	init_player(&game->player);
	game->is_paused = false;
	return (game);
}
