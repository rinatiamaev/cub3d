/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:08:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:44:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_manhattan_dist_point(t_point a, t_point b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
}

double	ft_cab_dist_dpoint(t_dpoint a, t_dpoint b)
{
	return (fabs(a.x - b.x) + fabs(a.y - b.y));
}

int	ft_euclidean_dist_point(t_point a, t_point b)
{
	return (sqrt(pow((double)a.x - (double)b.x, 2)
			+ pow((double)a.y - (double)b.y, 2)));
}

double	ft_euclidean_dist_dpoint(t_dpoint a, t_dpoint b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}
