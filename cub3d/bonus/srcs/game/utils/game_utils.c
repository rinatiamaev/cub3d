/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:08:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 16:28:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	get_delta_time(void)
{
	struct timeval	tv;
	double			current_time;
	static double	last_time;
	double			delta_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	if (last_time == 0.0)
		last_time = current_time;
	delta_time = current_time - last_time;
	last_time = current_time;
	return (delta_time);
}

t_door	*find_door_at(t_game *game, t_point pos)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i]->pos.x == pos.x
			&& game->doors[i]->pos.y == pos.y)
			return (game->doors[i]);
		i++;
	}
	return (NULL);
}

bool	is_within_bounds(t_game *game, t_point pos)
{
	return (pos.x >= 0 && pos.x < game->map->size.x
		&& pos.y >= 0 && pos.y < game->map->size.y);
}

int	handle_game_state(t_game *game)
{
	if (game->state == GAME_OVER)
	{
		draw_lose_message(game);
		return (0);
	}
	else if (game->state == WIN)
	{
		draw_win_message(game);
		return (0);
	}
	else if (game->state != RUNNING)
		return (0);
	return (1);
}
