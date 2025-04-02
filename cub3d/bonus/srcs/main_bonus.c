/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:04:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 02:44:22 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error(NULL, "Usage: ./cub3d <map_file>");
	game = init_game(argv[1]);
	handle_event_hooks(game, game->window);
	mlx_loop(game->mlx);
	return (0);
}
