/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:07:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/22 18:45:56 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	get_dot_product(t_dpoint vec1, t_dpoint vec2)
{
	double	product_x;
	double	product_y;
	double	dot_product;

	product_x = vec1.x * vec2.x;
	product_y = vec1.y * vec2.y;
	dot_product = product_x + product_y;
	return (dot_product);
}


// Compute a raw direction vector
// from point 'from' to point 'to' (not normalized)
static t_dpoint	get_direction_vector(t_dpoint from, t_dpoint to)
{
	t_dpoint	vector;

	vector.x = to.x - from.x;
	vector.y = to.y - from.y;
	return (vector);
}

// Return a normalized vector (unit vector) based on the given vector
static t_dpoint	get_normalized_vector(t_dpoint vector)
{
	double		length;
	t_dpoint	unit_vector;

	length = sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length == 0)
		return ((t_dpoint){0, 0});
	unit_vector.x = vector.x / length;
	unit_vector.y = vector.y / length;
	return (unit_vector);
}


// Return a unit vector directly from point 'from' to point 'to'
t_dpoint	get_unit_direction_vector(t_dpoint from, t_dpoint to)
{
	t_dpoint	direction_vector;
	t_dpoint	unit_vector;

	direction_vector = get_direction_vector(from, to);
	unit_vector = get_normalized_vector(direction_vector);
	return (unit_vector);
}

