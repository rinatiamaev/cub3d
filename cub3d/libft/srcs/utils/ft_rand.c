/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:13:54 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/01 20:49:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	simple_hash(int seed)
{
	seed ^= seed >> 5;
	seed *= 2654435761;
	seed ^= seed >> 7;
	return (seed & 0xFFFF);
}

int	ft_time_seeded_rand(void)
{
	struct timeval	tv;
	int				seed;
	
	gettimeofday(&tv, NULL);
	seed = (int)((tv.tv_sec ^ tv.tv_usec) & 0xFFFFFFFF);
	return (simple_hash(seed));
}
