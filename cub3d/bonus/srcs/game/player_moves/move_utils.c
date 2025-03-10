/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:12:02 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/10 02:08:35 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_any_npc_talking(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->npc_count)
	{
		if (game->npcs[i]->state == NPC_STATE_SPEAK)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_candidate_near_any_npc(t_dpoint candidate, t_game *game,
	double min_distance)
{
	t_npc	*npc;
	double	distance;
	int		i;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		distance = ft_cab_dist_dpoint(candidate, npc->pos);
		if (distance < min_distance)
			return (true);
		i++;
	}
	return (false);
}

bool	can_move(t_game *game, double next_x, double next_y)
{
	t_dpoint	candidate;
	t_door		*door;

	if (is_any_npc_talking(game))
		return (false);
	candidate.x = next_x;
	candidate.y = next_y;
	if (game->map->matrix[(int)next_y][(int)next_x] == WALL)
		return (false);
	if (game->map->matrix[(int)next_y][(int)next_x] == DOOR)
	{
		door = find_door_at(game, (t_point){(int)next_x, (int)next_y});
		if (!door || (door->state != DOOR_OPEN))
			return (false);
	}
	if (is_candidate_near_any_npc(candidate, game, 0.5))
		return (false);
	return (true);
}
