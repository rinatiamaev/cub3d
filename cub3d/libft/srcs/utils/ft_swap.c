/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:06:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 10:23:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**ft_swap()
 * Swaps the values of two variables of any type.
 *
 * @a: Pointer to the first variable.
 * @b: Pointer to the second variable.
 * @size: The size (in bytes) of the data type to swap.
 *
 * Usage:
 * - Use this function to swap variables of any type (int, float, double,
 * structs, etc.).
 * - Ensure `size` matches the type size (e.g., `sizeof(int)`, `sizeof(double)`,
 * `sizeof(struct)`...).
 */
void	ft_swap(void *a, void *b, size_t size)
{
	void	*tmp;

	if (!a || !b || size == 0)
		return ;
	tmp = malloc(size);
	if (!tmp)
		return ;
	ft_memcpy(tmp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, tmp, size);
	free(tmp);
}
