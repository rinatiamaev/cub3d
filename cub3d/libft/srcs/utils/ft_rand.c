/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:13:54 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/04 21:54:33 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	xorshift32(unsigned int *state)
{
	*state ^= *state << 13;
	*state ^= *state >> 17;
	*state ^= *state << 5;
	return (*state);
}

int	ft_rand(int min, int max)
{
	static unsigned int	state;
	struct timeval		tv;

	if (state == 0)
	{
		gettimeofday(&tv, NULL);
		state = (unsigned int)(tv.tv_sec ^ tv.tv_usec);
	}
	return (min + (xorshift32(&state) % (max - min + 1)));
}
