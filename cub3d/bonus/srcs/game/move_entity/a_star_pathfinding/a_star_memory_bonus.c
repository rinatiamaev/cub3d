/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_memory_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:59:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:38:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Frees all dynamically allocated nodes from the A* search tree.
 *
 * This function iterates through the singly linked list of A* nodes starting
 * from `astar->node`, freeing each node in sequence. These nodes were
 * previously created during the expansion process in the A* algorithm and
 * stored using the `next` pointer for cleanup purposes.
 *
 * After all nodes are freed, the `astar->node` pointer is set to NULL to
 * indicate that the list has been deallocated.
 *
 * @param astar Pointer to the A* structure containing the node list.
 */
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

/**
 * @brief Frees the memory used by the A* closed list (priority queue).
 *
 * This function deallocates the array of node pointers used in the closed list,
 * which stores the nodes already evaluated by the A* algorithm. It resets the
 * list's size and capacity to 0, and nullifies the internal pointer to prevent
 * dangling references.
 *
 * @param closed_list Pointer to the closed list structure to free.
 */
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

/**
 * @brief Resets and frees all dynamic data in the A* pathfinding structure.
 *
 * This function deallocates all memory used by the A* algorithm's internal
 * structures, including the node chain, the closed list (priority queue),
 * and the open list (2D grid of visited flags). After cleanup, all pointers
 * are nullified to avoid dangling references.
 *
 * @param game Pointer to the game context (used for map size reference).
 * @param astar Pointer to the A* data structure to reset.
 */
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
