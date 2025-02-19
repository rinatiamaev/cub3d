/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:40:38 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 14:20:19 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_memcpy()
 * Copies `n` bytes from `src` to `dest`.
 *
 * @dest: Destination memory block.
 * @src: Source memory block.
 * @n: Number of bytes to copy.
 *
 * Returns: `dest` on success, or NULL if `dest` or `src` is NULL.
 *
 * Notes:
 * - `ft_memcpy()` does **not** handle overlapping memory regions
 * (use `ft_memmove()` for that).
 * - If `n == 0`, it simply returns `dest`.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest || !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
