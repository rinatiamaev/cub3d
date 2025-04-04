/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_setup_bonus_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:55:06 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:36:02 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Creates and initializes the closed list for A* pathfinding.
 *
 * In the A* algorithm, the closed list keeps track of nodes that have
 * already been visited and evaluated. This function allocates and
 * initializes a t_closed_list structure with enough capacity to hold
 * all possible nodes in the map (width * height).
 *
 * - The `capacity` is set to the total number of grid cells.
 * - The `nodes` array is allocated to store pointers to t_node structs.
 * - The `size` is initialized to 0, meaning the list is empty.
 *
 * This data structure helps avoid redundant processing by ensuring
 * that nodes already visited are not revisited, thereby improving
 * the algorithm’s performance.
 *
 * @param game Pointer to the game context, used for memory allocation.
 * @return Pointer to the newly allocated and initialized closed list.
 */
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

/**
 * @brief Initializes a 2D array used as the open list in A* pathfinding.
 *
 * In the A* algorithm, the open list is used to track map cells (nodes)
 * that are yet to be evaluated. This function allocates a 2D array where
 * each cell is an `int` indicating whether a node is in the open list.
 *
 * - The array is allocated with dimensions [height][width], based on the
 *   map size.
 * - Each cell is initialized to 0 (meaning not in the open list).
 * - If allocation fails at any point, previously allocated rows are freed
 *   and an error is triggered via the game's error handler.
 *
 * This structure is useful to avoid revisiting nodes that are already
 * scheduled for evaluation.
 *
 * @param game Pointer to the game context, used for memory allocation
 *             and error handling.
 * @return A pointer to the newly allocated and initialized 2D array.
 */
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

/**
 * @brief Creates and initializes the starting node for A* pathfinding.
 *
 * This function allocates and sets up the start node, which represents the
 * beginning of the path to the goal in the A* algorithm.
 *
 * - The `pos` is set to the given start coordinate.
 * - The `g_cost` (cost from start to current node) is 0.
 * - The `h_cost` (heuristic estimate to goal) is computed using the
 *   Manhattan distance between `start` and the `goal` from the astar struct.
 * - The `f_cost` is the total cost estimate: `f = g + h`.
 * - The `next` pointer is set to NULL (for linked list use).
 * - The `parent` pointer is also NULL as this is the starting point.
 *
 * This node acts as the root of the search tree for the algorithm.
 *
 * @param game  Pointer to the game context (for allocation and errors).
 * @param astar Pointer to the A* data structure containing the goal.
 * @param start The starting map position as a grid coordinate.
 * @return A pointer to the initialized start node.
 */
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

/**
 * @brief Initializes the A* pathfinding structure for a new search.
 *
 * This function prepares the `t_astar` struct before performing a pathfinding
 * operation. It resets any previous state and sets up all necessary
 * components:
 *
 * - Resets the internal state using `reset_astar_struct`.
 * - Sets the goal position used to calculate heuristics.
 * - Allocates the closed list to keep track of visited nodes.
 * - Creates the open list as a 2D grid to mark which nodes are pending.
 * - Initializes the start node with cost values and sets it as the root.
 *
 * @param game  Pointer to the game context (used for memory management).
 * @param astar Pointer to the A* structure to initialize.
 * @param start Starting grid coordinate for the path.
 * @param goal  Target grid coordinate the path should lead to.
 */
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
