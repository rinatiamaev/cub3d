/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_heap_utils_bonus_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:08:53 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:42:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Swaps two node pointers.
 *
 * This utility function exchanges the values of two pointers to t_node
 * structures. It is typically used to maintain the heap property during
 * operations like heapify-up and heapify-down.
 *
 * @param a Pointer to the first node pointer.
 * @param b Pointer to the second node pointer.
 */
static void	swap_nodes(t_node **a, t_node **b)
{
	t_node	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Restores the min-heap property by moving a node up the heap.
 *
 * This function is called after a new node is inserted into the closed list's
 * binary heap. It ensures the min-heap property is preserved by comparing
 * the inserted node with its parent. If the inserted node has a lower f_cost
 * than its parent, the two nodes are swapped. This process continues until
 * the node is in a valid position or the root is reached.
 *
 * In a binary heap stored as an array:
 *   - Left  child index = 2 * parent_index + 1
 *   - Right child index = 2 * parent_index + 2
 *   - Parent index      = (child_index - 1) >> 1
 *
 * @param closed_list Pointer to the min-heap (closed list).
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

/**
 * @brief Inserts a node into the closed list min-heap.
 *
 * This function inserts a node into the binary heap used as the closed list.
 * If the current size of the heap has reached its capacity, the capacity is
 * doubled using reallocation. The node is added at the end of the heap array,
 * and `heapify_up` is called to restore the min-heap property based on the
 * node's f_cost (total estimated cost).
 *
 * Maintaining the heap structure is essential for efficiently accessing the
 * node with the lowest f_cost during the A* pathfinding algorithm.
 *
 * @param closed_list The binary heap that stores visited nodes.
 * @param node The node to be inserted into the heap.
 * @param game A pointer to the game context used for memory management.
 */
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

/**
 * @brief Restores the min-heap property after node extraction.
 *
 * This function is used after removing the root node (with the smallest f_cost)
 * from the closed list. It restores the min-heap property by repeatedly
 * comparing the current node to its children. If one of the children has a
 * smaller f_cost, it swaps with the smallest child and continues the process.
 *
 * This ensures that the node with the lowest f_cost is promoted to the root
 * of the heap. Maintaining this property is essential for ensuring that the
 * A* algorithm always expands the most promising node first.
 *
 * The binary heap is represented as an array, with index formulas:
 *  - Left child:  2 * index + 1
 *  - Right child: 2 * index + 2
 *
 * @param closed_list The binary heap storing nodes sorted by f_cost.
 * @param index Index from which to start heapifying down.
 */
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

/**
 * @brief Extracts the node with the lowest f_cost from the closed list.
 *
 * This function removes and returns the node with the smallest f_cost from
 * the min-heap, which is used as a priority queue in the A* algorithm.
 * 
 * After removing the root node (index 0), the last node in the heap is moved
 * to the root to maintain the complete binary tree structure. Then
 * `heapify_down()` is called to restore the min-heap property.
 * 
 * This operation ensures that the next time a node is extracted, it is the one
 * with the lowest total estimated cost (f_cost = g_cost + h_cost).
 *
 * @param closed_list The priority queue implemented as a binary min-heap.
 * @return Pointer to the extracted node with the smallest f_cost.
 */
t_node	*closed_list_extract_min(t_closed_list *closed_list)
{
	t_node	*min_node;

	min_node = closed_list->nodes[0];
	closed_list->size--;
	closed_list->nodes[0] = closed_list->nodes[closed_list->size];
	heapify_down(closed_list, 0);
	return (min_node);
}
