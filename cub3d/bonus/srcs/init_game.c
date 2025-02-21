/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:19:05 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/21 11:39:05 by nlouis           ###   ########.fr       */
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
	// Adjust the player's initial position to be centered in the cell
	player->pos = (t_dpoint){player->pos.x + 0.5, player->pos.y + 0.5};

	// Set default speeds
	player->rot_speed = 5;
	player->move_speed = 0.05;
	
	// Set the player's angle based on the configuration direction.
	// For example:
	if (player->conf_dir == 'N')
		player->angle = 3 * M_PI / 2;  // Facing up (270°)
	else if (player->conf_dir == 'S')
		player->angle = M_PI / 2;      // Facing down (90°)
	else if (player->conf_dir == 'W')
		player->angle = M_PI;          // Facing left (180°)
	else if (player->conf_dir == 'E')
		player->angle = 0;             // Facing right (0°)

	// Calculate the player's direction vector from the angle.
	player->dir.x = cos(player->angle);
	player->dir.y = sin(player->angle);

	// Calculate the camera plane vector (perpendicular to the direction).
	// The constant 0.66 determines the field of view.
	player->plane.x = -sin(player->angle) * 0.66;
	player->plane.y = cos(player->angle) * 0.66;
}

static void	init_witchKitty(t_game *game, t_npc *npc)
{
	char			*paths[] = {WITCH_REST1, WITCH_REST2, WITCH_REST3, 
						WITCH_REST4, WITCH_REST5, WITCH_REST6};
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
	ft_print_matrix(game->map->matrix, game->map->size.y, game->map->size.x);
	game->window = x_calloc(game, 1, sizeof(t_window));
	init_window(game, game->window);
	load_walls(game, game->map->conf);
	init_witchKitty(game, game->witch_kitty);
	init_player(&game->player);
	game->is_paused = false;
	return (game);
}
