/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:59:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/02 02:23:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_astar_nodes(t_astar *astar)
{
	t_node	*current;
	t_node	*temp;

	current = astar->node;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	astar->node = NULL;
}

static void	free_priority_queue(t_closed_list *closed_list)
{
	if (!closed_list)
		return ;
	if (closed_list->nodes)
	{
		free(closed_list->nodes);
		closed_list->nodes = NULL;
	}
	closed_list->size = 0;
	closed_list->capacity = 0;
}

void	reset_astar_struct(t_game *game, t_astar *astar)
{
	int	y;

	if (!astar)
		return ;
	free_astar_nodes(astar);
	if (astar->closed_list)
	{
		free_priority_queue(astar->closed_list);
		free(astar->closed_list);
		astar->closed_list = NULL;
	}
	if (astar->open_list)
	{
		y = 0;
		while (y < game->map->size.y)
		{
			if (astar->open_list[y])
				free(astar->open_list[y]);
			y++;
		}
		free(astar->open_list);
		astar->open_list = NULL;
	}
}
