/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:02:28 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/02 21:57:06 by nlouis           ###   ########.fr       */
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

static void	init_door(t_game *game, t_door *door, t_dpoint pos)
{
	door->pos = pos;
	door->size = (t_point){128, 128};
	door->state = DOOR_CLOSED;
	load_single_xpm(game, &door->tex, DOOR0, game->mlx);
	door->speed = 1.0;
}

void	place_door(t_game *game, double x, double y)
{
	t_door		*door;
	t_dpoint	pos;

	door = x_calloc(game, 1, sizeof(t_door));
	pos = (t_dpoint){x, y};
	init_door(game, door, pos);
	load_single_xpm(game, &door->tex, DOOR0, game->mlx);
	update_door_list(game, door);
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
				door->open_timer = 4.0;
			}
		}
		else if (door->state == DOOR_CLOSING)
		{
			door->offset -= door->speed * delta_time;
			if (door->offset <= 0.0)
			{
				door->offset = 0.0;
				door->state = DOOR_CLOSED;
			}
		}
		else if (door->state == DOOR_OPEN)
		{
			door->open_timer -= delta_time;
			if (door->open_timer <= 0)
				door->state = DOOR_CLOSING;
		}
		i++;
	}
}

void	interact_with_door(t_game *game)
{
	t_door	*door;
	int		i;

	i = 0;
	while (i < game->door_count)
	{
		door = game->doors[i];
		if (ft_manhattan_dist_dpoint(game->player.pos, door->pos) <= 4.0)
		{
			if (door->state == DOOR_CLOSED)
				door->state = DOOR_OPENING;
			else if (door->state == DOOR_OPEN)
				door->state = DOOR_CLOSING;
			return ;
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
