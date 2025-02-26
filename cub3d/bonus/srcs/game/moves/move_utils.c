/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:12:02 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/26 22:37:18 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_candidate_near_any_sprite(t_dpoint candidate, t_game *game,
	double min_distance)
{
	t_sprite		*sprite;
	t_dpoint		dist;
	double			distance;
	int				i;

	i = 0;
	while (i < game->sprite_count)
	{
		sprite = game->sprites[i];
		dist.x = candidate.x - sprite->pos.x;
		dist.y = candidate.y - sprite->pos.y;
		distance = sqrt(dist.x * dist.x + dist.y * dist.y);
		if (distance < min_distance)
			return (true);
		i++;
	}
	return (false);
}

bool	can_move(t_game *game, double next_x, double next_y)
{
	t_dpoint	candidate;

	candidate.x = next_x;
	candidate.y = next_y;
	if (game->map->matrix[(int)next_y][(int)next_x] == 1)
		return (false);
	if (is_candidate_near_any_sprite(candidate, game, 0.5))
		return (false);
	return (true);
}
