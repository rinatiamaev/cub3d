/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:12:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:55:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Handles critical errors by freeing resources and exiting.
 *
 * This function performs a graceful shutdown of the game upon encountering
 * a critical error. It first frees all allocated game resources (if the
 * game pointer is valid), then prints the given error message to stderr.
 *
 * If the global errno is set, the function also prints a system error
 * message using perror. Finally, it exits the program with EXIT_FAILURE.
 *
 * @param game Pointer to the game state to be cleaned up.
 * @param err_msg Optional error message to be printed to stderr.
 */
void	error(t_game *game, char *err_msg)
{
	if (game)
		free_game(game);
	if (err_msg)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putendl_fd(err_msg, STDERR_FILENO);
	}
	if (errno)
		perror("");
	exit(EXIT_FAILURE);
}
