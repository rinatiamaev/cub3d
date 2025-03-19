/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_door_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:01:35 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/19 10:01:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_door_list(t_game *game, t_door *door)
{
	game->doors = x_realloc(game, game->doors,
			game->door_count * sizeof(t_door *),
			(game->door_count + 1) * sizeof(t_door *));
	game->doors[game->door_count] = door;
	game->door_count++;
}
