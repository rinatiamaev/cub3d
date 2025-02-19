/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 07:55:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/15 13:31:00 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_in_longlong_range(const char *str, bool negative)
{
	unsigned long long	limit;
	unsigned long long	sum;
	int					digit;

	if (negative)
		limit = (unsigned long long)LLONG_MAX + 1ULL;
	else
		limit = (unsigned long long)LLONG_MAX;
	sum = 0;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (false);
		digit = *str - '0';
		if (sum > (limit - digit) / 10ULL)
			return (false);
		sum = sum * 10ULL + digit;
		str++;
	}
	return (true);
}

bool	ft_is_valid_integer(const char *str)
{
	bool	negative;

	if (!str || !*str)
		return (false);
	negative = false;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative = true;
		str++;
	}
	if (!*str)
		return (false);
	if (!is_in_longlong_range(str, negative))
		return (false);
	return (true);
}
