/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:02:28 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 11:49:40 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_door_list(t_game *game, t_door *door)
{
	game->doors = x_realloc(game, game->doors,
			game->door_count * sizeof(t_door *),
			(game->door_count + 1) * sizeof(t_door *));
	game->doors[game->door_count] = door;
	game->door_count++;
}

void	place_door(t_game *game, double x, double y)
{
	t_door		*door;

	door = x_calloc(game, 1, sizeof(t_door));
	door->pos = (t_dpoint){x, y};
	door->size = (t_point){128, 128};
	door->state = DOOR_CLOSED;
	door->speed = 1.0;
	update_door_list(game, door);
}

static bool	is_player_on_door(t_game *game, t_door *door)
{

	// Check if player is exactly on the door tile
	if ((int)game->player.pos.x == (int)door->pos.x &&
		(int)game->player.pos.y == (int)door->pos.y)
		return (true);

	return (false);
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
		{
			door->offset += door->speed * delta_time;
			if (door->offset >= 1.0)
			{
				door->offset = 1.0;
				door->state = DOOR_OPEN;
				door->open_timer = 3.0;
			}
		}
		else if (door->state == DOOR_CLOSING)
		{
			if (is_player_on_door(game, door))
			{
				door->state = DOOR_OPEN;
				door->open_timer = 3.0;
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
		else if (door->state == DOOR_OPEN)
		{
			if (is_player_on_door(game, door))
				door->open_timer = 3.0;
			else
			{
				door->open_timer -= delta_time;
				if (door->open_timer <= 0.0)
					door->state = DOOR_CLOSING;
			}
		}
		i++;
	}
}


t_door	*find_door_at(t_game *game, t_point pos)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i]->pos.x == pos.x && game->doors[i]->pos.y == pos.y)
			return (game->doors[i]);
		i++;
	}
	return (NULL);
}
