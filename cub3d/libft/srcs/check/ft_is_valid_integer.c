/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_integer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 07:55:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:43:16 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * is_in_longlong_range()
 * Checks whether the given numeric string can be safely stored 
 * within the range of a `long long` integer.
 *
 * @str: The numeric string to validate (excluding the sign).
 * @negative: A boolean indicating whether the number is negative.
 *
 * Returns: true if the number is within the range of `long long`,
 * false otherwise.
 *
 * - The function ensures that the number does not exceed LLONG_MAX 
 *   (or LLONG_MIN in case of a negative number).
 * - It processes the string digit by digit, checking for overflow.
 */
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

/**
 * ft_is_valid_integer()
 * Checks whether a given string represents a valid integer.
 *
 * @str: The string to validate.
 *
 * Returns: true if the string represents a valid `long long` integer,
 * false otherwise.
 *
 * Usage:
 * - Use `ft_is_valid_integer()` to verify if a string can be converted
 *   into a valid signed integer without overflow.
 * - The function allows an optional '+' or '-' sign at the beginning.
 * - It ensures that the string is not empty after the sign and 
 *   that all characters are digits.
 * - It prevents numeric overflows by checking `LLONG_MAX` and `LLONG_MIN`.
 */
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
