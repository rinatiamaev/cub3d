/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:22:16 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 23:22:25 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

double	get_fractional_part(double value)
{
	double	integer_part;
	double	decimal_part;

	integer_part = floor(value);
	decimal_part = value - integer_part;
	return (decimal_part);
}

double	wrap_in_range(double value, double range)
{
	if (value < 0.0)
		value += range;
	else if (value >= range)
		value -= range;
	return (value);
}
