/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_path_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:08:53 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/19 12:20:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	reconstruct_path(t_game *game, t_node *goal_node, t_npc *npc)
{
	t_node	*current;
	int		path_length;

	path_length = 0;
	current = goal_node;
	while (current)
	{
		path_length++;
		current = current->parent;
	}
	if (npc->path)
		free(npc->path);
	npc->path_length = path_length;
	npc->path_index = 0;
	npc->path = x_calloc(game, path_length, sizeof(t_dpoint));
	current = goal_node;
	while (current)
	{
		npc->path[--path_length]
			= (t_dpoint){current->pos.x + 0.5, current->pos.y + 0.5};
		current = current->parent;
	}
}

void	a_star_path(t_game *game, t_npc *npc, t_point start, t_point goal)
{
	t_astar	*astar;

	astar = npc->astar;
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
			reconstruct_path(game, astar->current_node, npc);
			return ;
		}
		spread_child_node(game, npc, astar);
	}
	npc->path_length = 0;
	npc->path_index = 0;
	free(npc->path);
	npc->path = NULL;
}
