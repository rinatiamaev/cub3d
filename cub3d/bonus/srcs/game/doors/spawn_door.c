/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:46:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/19 10:20:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	spawn_door(t_game *game, double x, double y)
{
	t_door		*door;

	door = x_calloc(game, 1, sizeof(t_door));
	door->pos = (t_dpoint){x, y};
	door->type = NORMAL_DOOR;
	door->state = DOOR_CLOSED;
	door->speed = 1.0;
	update_door_list(game, door);
}
