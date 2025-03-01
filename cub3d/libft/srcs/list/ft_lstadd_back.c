/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:50:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/25 13:55:48 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstadd_back()
 * Adds a new node to the end of a linked list.
 *
 * @lst: A pointer to the first node of the list.
 * @new: The new node to be added at the end.
 *
 * Returns: Nothing (void).
 *
 * Usage:
 * - Use `ft_lstadd_back()` to append a node to an existing linked list.
 * - If the list is empty (`*lst == NULL`), the new node becomes the 1st node.
 * - Uses `ft_lstlast()` to find the last node before appending.
 * - Does nothing if `lst` or `new` is NULL.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
