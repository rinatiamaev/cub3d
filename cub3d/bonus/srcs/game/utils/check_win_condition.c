/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_win_condition.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:06 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:13:41 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_npc_near_exit(t_npc *npc, t_game *game)
{
	int				i;
	t_door			*door;
	const double	max_dist = 8.0;

	i = 0;
	while (i < game->door_count)
	{
		door = game->doors[i];
		if (door->type == EXIT_DOOR_TYPE)
		{
			if (ft_euclidean_dist_dpoint(npc->pos, door->pos) <= max_dist)
				return (true);
		}
		i++;
	}
	return (false);
}

static void	update_saved_npcs(t_game *game)
{
	int	i;

	if (game->state != WIN)
		return ;
	i = 0;
	while (i < game->npc_count)
	{
		if (is_npc_near_exit(game->npcs[i], game))
			game->npcs[i]->is_saved = true;
		i++;
	}
}

void	check_win_condition(t_game *game)
{
	t_point	player_pos;
	t_door	*door;

	player_pos.x = (int)game->player.pos.x;
	player_pos.y = (int)game->player.pos.y;
	if (game->map->matrix[player_pos.y][player_pos.x] == EXIT_DOOR)
	{
		door = find_door_at(game, (t_point){player_pos.x, player_pos.y});
		if (door && door->state == DOOR_OPEN)
		{
			game->state = WIN;
			update_saved_npcs(game);
		}
	}
}
