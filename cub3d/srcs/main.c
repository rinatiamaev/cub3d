/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:04:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 18:35:45 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error(NULL, "Usage: ./cub3d <map_file>");
	game = init_game(argv[1]);
	printf("Map dimension: %d x %d\n", game->map->max_width, game->map->row_count);
	printf("Cell at player's position: %d\n", game->map->matrix[(int)game->player.pos.y][(int)game->player.pos.x]);
	handle_event_hooks(game, game->window);
	mlx_loop(game->mlx);
	free_game(game);
	return (0);
}
