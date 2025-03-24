/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:54:08 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:43:50 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstnew()
 * Creates a new node for a linked list.
 *
 * @content: A pointer to the content that the new node should store.
 *
 * Returns: A pointer to the newly allocated node,
 * or NULL if memory allocation fails.
 *
 * Usage:
 * - Use `ft_lstnew()` to create an isolated node with the given content.
 * - The `next` pointer is initialized to NULL.
 * - The caller is responsible for managing the memory of `content` if needed.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
