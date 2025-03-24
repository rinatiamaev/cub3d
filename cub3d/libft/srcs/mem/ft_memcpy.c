/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:40:38 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:45:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d8;
	const unsigned char	*s8;

	d8 = (unsigned char *)dest;
	s8 = (const unsigned char *)src;
	if (!dest || !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (n >= 8)
	{
		*(uint64_t *)d8 = *(const uint64_t *)s8;
		d8 += 8;
		s8 += 8;
		n -= 8;
	}
	while (n--)
		*d8++ = *s8++;
	return (dest);
}
