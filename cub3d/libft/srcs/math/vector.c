/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:07:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 23:26:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	get_vector_length(t_dpoint vec)
{
	double	length_squared;

	length_squared = vec.x * vec.x + vec.y * vec.y;
	return (sqrt(length_squared));
}

t_dpoint	divide_vector_by_scalar(t_dpoint vec, double scalar)
{
	t_dpoint	result;

	result.x = vec.x / scalar;
	result.y = vec.y / scalar;
	return (result);
}

t_dpoint	get_normalized_vector(t_dpoint vector)
{
	double		length;
	t_dpoint	unit_vector;

	length = get_vector_length(vector);
	if (length == 0)
		return ((t_dpoint){0, 0});
	unit_vector = divide_vector_by_scalar(vector, length);
	return (unit_vector);
}
