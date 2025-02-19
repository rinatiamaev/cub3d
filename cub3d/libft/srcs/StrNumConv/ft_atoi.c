/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 21:00:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/01/31 08:05:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_check_overflow(long long num, char digit, int sign)
{
	long long	cutoff;

	if (sign == 1)
		cutoff = INT_MAX / 10;
	else
		cutoff = (-(long long)INT_MIN) / 10;
	if (sign == 1)
	{
		if (num > cutoff || (num == cutoff && (digit - '0') > (INT_MAX % 10)))
			return (true);
	}
	else
	{
		if (-num > -((long long)INT_MIN / 10)
			|| (-num == -((long long)INT_MIN / 10)
				&& (digit - '0') > ((-(long long)INT_MIN) % 10)))
			return (true);
	}
	return (false);
}

long long	ft_atoi(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		if (ft_check_overflow(num, *str, sign))
			return (ATOI_ERROR);
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((int)num * sign);
}
