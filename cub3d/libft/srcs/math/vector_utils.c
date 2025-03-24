/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:25:23 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:44:17 by nlouis           ###   ########.fr       */
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

t_dpoint	get_direction_vector(t_dpoint from, t_dpoint to)
{
	t_dpoint	vector;

	vector.x = to.x - from.x;
	vector.y = to.y - from.y;
	return (vector);
}

double	get_vector_angle(t_dpoint vector)
{
	double	angle;

	angle = atan2(vector.y, vector.x);
	return (angle);
}

double	get_vector_angle_between(t_dpoint from, t_dpoint to)
{
	t_dpoint	direction_vector;
	double		angle;

	direction_vector = get_direction_vector(from, to);
	angle = get_vector_angle(direction_vector);
	return (angle);
}

t_dpoint	get_unit_direction_vector(t_dpoint from, t_dpoint to)
{
	t_dpoint	direction_vector;
	t_dpoint	unit_vector;

	direction_vector = get_direction_vector(from, to);
	unit_vector = get_normalized_vector(direction_vector);
	return (unit_vector);
}
