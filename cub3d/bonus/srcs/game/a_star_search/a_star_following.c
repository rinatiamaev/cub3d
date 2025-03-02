/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_for_enemy_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 07:18:04 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/11 09:07:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* t_node	*a_star_following(t_game *game, t_astar *astar, t_point start,
			t_point goal)
{
	setup_astar_struct(game, astar, start, goal);
	closed_list_insert(astar->closed_list, astar->node, game);
	while (astar->closed_list->size > 0)
	{
		astar->current_node = closed_list_extract_min(astar->closed_list);
		astar->open_list
		[astar->current_node->pos.y][astar->current_node->pos.x] = 1;
		if (astar->current_node->pos.x == astar->goal.x
			&& astar->current_node->pos.y == astar->goal.y)
		{
			return (astar->current_node);
		}
		spread_child_node(game, astar);
	}
	return (NULL);
} */
