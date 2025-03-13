/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_setup_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:55:06 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 17:09:17 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*This function creates and initializes the closed list (visited nodes). First
it allocates memory for it, then set the capacity based on the number of cell
in the grid to know how many nodes it can potentially contain. It then alloctes
enough memory for an array of pointers to t_node objects, based on the closed
list's capacity. Finally, it sets the size of closed list to 0 meaning it's 
empty for now.*/
static t_closed_list	*create_closed_list(t_game *game)
{
	t_closed_list	*closed_list;

	closed_list = x_malloc(game, sizeof(t_closed_list));
	closed_list->capacity = game->map->size.x * game->map->size.y;
	closed_list->nodes = x_malloc(game, sizeof(t_node *)
			* closed_list->capacity);
	closed_list->size = 0;
	return (closed_list);
}

/*This function initializes a 2D array that serves as the open list, it is 
used to keep track of which positions (or nodes) on the map that are yet to
be evaluated during the pathfinding process. It first allocate memory for an
array of pointers, then initialies each row with 0. */
static int	**create_open_list(t_game *game)
{
	int	**open_list;
	int	y;

	open_list = (int **)x_malloc(game, sizeof(int *) * game->map->size.y);
	y = 0;
	while (y < game->map->size.y)
	{
		open_list[y]
			= (int *)x_calloc(game, game->map->size.x, sizeof(int));
		if (!open_list[y])
		{
			while (--y >= 0)
				free(open_list[y]);
			free(open_list);
			error(game, "Memory allocation failed");
		}
		y++;
	}
	return (open_list);
}

/*This function initializes the starting node. This node represnts the starting
position for the path to the goal. It first allocates memory for a node. Then
initializes this node. Sets the the next pointer to NULL, the node's pos to
the starting pos, g_cost to 0 because it represents the cost from itself
to itself, the h_cost is set using Manhattan Distance (which calculates
the number of horizontal and vertical moves needed to reach the goal), 
the f_cost is the total estimated cost by additioning g_cost to h_cost, finally
sets the parent pointer to NULL because the start node has no predecessor.*/
static t_node	*create_start_node(t_game *game, t_astar *astar, t_point start)
{
	t_node	*start_node;

	start_node = x_malloc(game, sizeof(t_node));
	start_node->next = NULL;
	start_node->pos = start;
	start_node->g_cost = 0;
	start_node->h_cost
		= ft_manhattan_dist_point(start_node->pos, astar->goal);
	start_node->f_cost = start_node->h_cost;
	start_node->parent = NULL;
	return (start_node);
}

void	setup_astar_struct(t_game *game, t_astar *astar, t_point start,
	t_point goal)
{
	if (!astar)
		return ;
	reset_astar_struct(game, astar);
	astar->goal = goal;
	astar->closed_list = create_closed_list(game);
	astar->open_list = create_open_list(game);
	astar->node = create_start_node(game, astar, start);
}
