/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:08:10 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 11:08:17 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	get_delta_time(void)
{
	static struct timeval	prev_time;
	struct timeval			current_time;
	double					delta_time;

	gettimeofday(&current_time, NULL);
	if (prev_time.tv_sec == 0 && prev_time.tv_usec == 0)
	{
		prev_time = current_time;
		return (0.0);
	}
	delta_time = (current_time.tv_sec - prev_time.tv_sec)
		+ (current_time.tv_usec - prev_time.tv_usec) / 1000000.0;
	prev_time = current_time;
	return (delta_time);
}