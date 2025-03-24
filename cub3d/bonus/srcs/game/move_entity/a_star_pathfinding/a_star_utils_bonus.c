/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 07:18:04 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:32:51 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*The create_child_node function generates a new node representing a potential
move. It allocates memory for the child node and initializes its position to
the specified pos. The function calculates the g_cost by adding 1 to the
current node’s g_cost, assuming a uniform movement cost. It then computes
the h_cost using the Manhattan distance from the child’s position to the goal,
and sums these to determine the f_cost. The new node’s parent is set to the
current node to facilitate path reconstruction. Additionally, the child node is
linked into a list by setting its next pointer to the current node. Finally,
the function returns the newly created and initialized child node for further
processing.*/

static t_node	*create_child_node(t_game *game, t_astar *astar, t_point pos)
{
	t_node	*child_node;

	child_node = (t_node *)x_calloc(game, 1, sizeof(t_node));
	child_node->pos = pos;
	child_node->g_cost = astar->current_node->g_cost + 1;
	child_node->h_cost = ft_manhattan_dist_point(pos, astar->goal);
	child_node->f_cost = child_node->g_cost + child_node->h_cost;
	child_node->parent = astar->current_node;
	child_node->next = astar->node;
	return (child_node);
}

static void	process_single_child(t_game *game, t_npc *npc, t_astar *astar,
															int direction)
{
	t_node	*child_node;
	t_point	new_pos;

	new_pos.x = astar->current_node->pos.x + astar->direction[direction].x;
	new_pos.y = astar->current_node->pos.y + astar->direction[direction].y;
	if (!is_position_valid_npc(game, npc, astar, new_pos))
		return ;
	child_node = create_child_node(game, astar, new_pos);
	astar->node = child_node;
	closed_list_insert(astar->closed_list, child_node, game);
}

void	spread_child_node(t_game *game, t_npc *npc, t_astar *astar)
{
	int	direction;

	direction = 0;
	while (direction < 4)
	{
		process_single_child(game, npc, astar, direction);
		direction++;
	}
}
