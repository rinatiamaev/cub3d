/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:04:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 00:57:02 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error(NULL, "Usage: ./cub3d <map_file>");
	game = init_game(argv[1]);
	ft_print_matrix(game->map->matrix, game->map->row_count, game->map->max_width);
	printf("Player position: %d, %d\n", game->player.pos.x, game->player.pos.y);
	printf("Player direction: %c\n", game->player.dir);
	printf("Player count: %d\n", game->map->player_count);
	printf("Ceiling color: %d\n", game->map->conf.ceiling_color);
	printf("Floor color: %d\n", game->map->conf.floor_color);
	free_game(game);
	return (0);
}
