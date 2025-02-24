/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/24 13:15:47 by nlouis           ###   ########.fr       */
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
	player->plane.x = -sin(player->angle) * 0.66; // Perpendicular X to `dir`
	player->plane.y = cos(player->angle) * 0.66;  // Perpendicular Y to `dir`
}


static void	init_witch_kitty(t_game *game, t_npc *npc)
{
	char			*paths[] = {WS0, WS1, WS2, WS3, WS4, WS5, WS6, WS7, WS8, WS9, WS10, WS11, WS12, WS13};
	int				num_frames;
	struct timeval	tv;
	
	num_frames = sizeof(paths) / sizeof(paths[0]);
	npc->pos = (t_dpoint){npc->pos.x + 0.5, npc->pos.y + 0.5};
	npc->num_frames = num_frames;
	npc->idle_frames = x_calloc(game, num_frames, sizeof(t_texture));
	load_textures_array(game, npc->idle_frames, num_frames, paths);
	gettimeofday(&tv, NULL);
	npc->anim_start = tv.tv_sec * 1000000L + tv.tv_usec;
}

t_game	*init_game(char *filename)
{
	t_game	*game;

	game = x_calloc(NULL, 1, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		error(game, "mlx_init() failed");
	game->map = init_map(game, filename);
	game->witch_kitty = x_calloc(game, 1, sizeof(t_npc));
	parse_map(game, game->map);
	game->window = x_calloc(game, 1, sizeof(t_window));
	init_window(game, game->window);
	load_walls(game, game->map->conf);
	init_witch_kitty(game, game->witch_kitty);
	init_player(&game->player);
	game->is_paused = false;
	return (game);
}
