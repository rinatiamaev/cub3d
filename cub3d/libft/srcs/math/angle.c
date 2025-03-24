/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:21:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 23:21:28 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	rad_to_deg(double radians)
{
	double	degrees;

	degrees = radians * (180.0 / M_PI);
	return (degrees);
}

double	deg_to_rad(double degrees)
{
	double	radians;

	radians = degrees * (M_PI / 180.0);
	return (radians);
}

double	wrap_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
