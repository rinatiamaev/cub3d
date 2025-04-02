/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_heap_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:08:53 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 01:19:32 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	swap_nodes(t_node **a, t_node **b)
{
	t_node	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*This function is used to ensure that the min-heap property is maintained
after inserting a new node in the closed list.
Each parent node has an f_cost less than or equal to its child nodes, ensuring
that the node with the smallest f_cost is always at the root of the heap.
@parent_index store the index of the parent node of the node being heapified.
The loop continues as long as the current node is not the root node, comparing
the node with its parent and swapping if necessary or the loop is broken if
the heap property is already maintained.
Claculate the parent index in a binary heap represented as an array:
	Left Child Index: 2 * parent_index + 1
	Right Child Index: 2 * parent_index + 2
	Parent Index: (child_index - 1) >> 1
*/
static void	heapify_up(t_closed_list *closed_list)
{
	int	index;
	int	parent_index;

	index = closed_list->size;
	while (index > 0)
	{
		parent_index = (index - 1) >> 1;
		if (closed_list->nodes[index]->f_cost
			>= closed_list->nodes[parent_index]->f_cost)
			break ;
		swap_nodes(&closed_list->nodes[index],
			&closed_list->nodes[parent_index]);
		index = parent_index;
	}
}

/*This function is used to add a new node to the closed list. First it checks
if the closed list has reach its capacity, it doubles it in this case. Then
it inserts the new node at the end of the closed_list->nodes array, maintaining
the integrity of the heap structure using heapify_up. Finally it increments 
the size of the closed list by one, which is essential for managing capacity
and correctly inserting following nodes*/
void	closed_list_insert(t_closed_list *closed_list, t_node *node,
	t_game *game)
{
	if (closed_list->size >= closed_list->capacity)
	{
		closed_list->capacity *= 2;
		closed_list->nodes = (t_node **)x_realloc(game, closed_list->nodes,
				sizeof(t_node *) * (closed_list->capacity >> 1),
				sizeof(t_node *) * closed_list->capacity);
	}
	closed_list->nodes[closed_list->size] = node;
	heapify_up(closed_list);
	closed_list->size++;
}

/*This function maintains the min-heap property of the closed list after
removing the smallest f_cost node. Starting from a given index(0), it
compares the current node’s f_cost with its left and right children. If a child
has a smaller f_cost, the function swaps the current node with the smallest
child. This process repeats until the current node is smaller than both
children or it reaches the heap's end. By doing so, heapify_down ensures
that the node with the smallest f_cost remains at the top of the heap.*/

static void	heapify_down(t_closed_list *closed_list, int index)
{
	int	smallest;
	int	left;
	int	right;

	while (2 * index +1 < closed_list->size)
	{
		smallest = index;
		left = (2 * index) + 1;
		right = (2 * index) + 2;
		if (left < closed_list->size
			&& closed_list->nodes[left]->f_cost
			< closed_list->nodes[smallest]->f_cost)
			smallest = left;
		if (right < closed_list->size
			&& closed_list->nodes[right]->f_cost
			< closed_list->nodes[smallest]->f_cost)
			smallest = right;
		if (smallest == index)
			break ;
		swap_nodes(&closed_list->nodes[index], &closed_list->nodes[smallest]);
		index = smallest;
	}
}

/* This function removes and returns the node with the smallest f_cost from
the min-heap (closed list). To reflect this removal, the size is decremented,
ensuring the heap’s boundary is maintained. After extraction, the last node
in the heap is moved to the root position to preserve the complete binary tree
structure. It then uses heapify_down to restore the heap order. This ensures
that the pathfinding algorithm accesses the next most promising node.*/
t_node	*closed_list_extract_min(t_closed_list *closed_list)
{
	t_node	*min_node;

	min_node = closed_list->nodes[0];
	closed_list->size--;
	closed_list->nodes[0] = closed_list->nodes[closed_list->size];
	heapify_down(closed_list, 0);
	return (min_node);
}
