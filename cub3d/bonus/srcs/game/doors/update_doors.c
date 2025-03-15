/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:02:28 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 14:10:18 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_player_on_door(t_game *game, t_door *door)
{
	if ((int)game->player.pos.x == (int)door->pos.x
		&& (int)game->player.pos.y == (int)door->pos.y)
		return (true);
	return (false);
}

static void	open_door(t_door *door, double delta_time)
{
	door->offset += door->speed * delta_time;
	if (door->offset >= 1.0)
	{
		door->offset = 1.0;
		door->state = DOOR_OPEN;
		door->open_timer = 1.5;
	}
}

static void	close_door(t_game *game, t_door *door, double delta_time)
{
	if (is_player_on_door(game, door))
	{
		door->state = DOOR_OPEN;
		door->open_timer = 1.5;
	}
	else
	{
		door->offset -= door->speed * delta_time;
		if (door->offset <= 0.0)
		{
			door->offset = 0.0;
			door->state = DOOR_CLOSED;
		}
	}
}

static void	handle_open_door(t_game *game, t_door *door, double delta_time)
{
	if (is_player_on_door(game, door))
		door->open_timer = 1.5;
	else
	{
		door->open_timer -= delta_time;
		if (door->open_timer <= 0.0)
			door->state = DOOR_CLOSING;
	}
}

void	update_doors(t_game *game, double delta_time)
{
	t_door	*door;
	int		i;

	i = 0;
	while (i < game->door_count)
	{
		door = game->doors[i];
		if (door->state == DOOR_OPENING)
			open_door(door, delta_time);
		else if (door->state == DOOR_CLOSING)
			close_door(game, door, delta_time);
		else if (door->state == DOOR_OPEN)
			handle_open_door(game, door, delta_time);
		i++;
	}
}
