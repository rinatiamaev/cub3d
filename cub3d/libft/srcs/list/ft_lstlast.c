/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:52:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/25 13:56:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstlast()
 * Returns the last node of a linked list.
 *
 * @lst: A pointer to the first node of the list.
 *
 * Returns: A pointer to the last node,
 * or NULL if the list is empty.
 *
 * Usage:
 * - Use `ft_lstlast()` to retrieve the last element of a linked list.
 * - The function iterates through the list until `next` is NULL.
 * - If `lst` is NULL, returns NULL.
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
