/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:08:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/11 23:52:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* double	get_delta_time(void)
{
	static struct timeval	prev_time;
	struct timeval			current_time;
	double					delta_time;

	gettimeofday(&current_time, NULL);
	if (prev_time.tv_sec == 0 && prev_time.tv_usec == 0)
	{
		prev_time = current_time;
		return (0.0);
	}
	delta_time = (current_time.tv_sec - prev_time.tv_sec)
		+ (current_time.tv_usec - prev_time.tv_usec) / 1000000.0;
	prev_time = current_time;
	return (delta_time);
} */

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
	printf("Delta Time: %f\n", delta_time); // Debug print need delete before EVAL
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
