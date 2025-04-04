/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:04:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:03:44 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Entry point of the Cub3D program.
 *
 * This function validates the command-line arguments and initializes the
 * game environment from the provided map file. It sets up event hooks for
 * user input and starts the main rendering loop via MiniLibX.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Returns 0 on successful execution.
 */
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
