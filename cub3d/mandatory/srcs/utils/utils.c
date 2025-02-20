/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:12:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 12:30:02 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	close_game(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (SUCCESS);
}
