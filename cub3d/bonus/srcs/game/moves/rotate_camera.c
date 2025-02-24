/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:18 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/24 11:05:17 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	wrap_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	rotate_left(t_player *player, double rot_speed, double delta_time)
{
	player->angle = wrap_angle(player->angle + rot_speed * delta_time);
	player->dir.x = cos(player->angle);
	player->dir.y = sin(player->angle);
	player->plane.x = -sin(player->angle) * 0.66;
	player->plane.y = cos(player->angle) * 0.66;
}

void	rotate_right(t_player *player, double rot_speed, double delta_time)
{
	player->angle = wrap_angle(player->angle - rot_speed * delta_time);
	player->dir.x = cos(player->angle);
	player->dir.y = sin(player->angle);
	player->plane.x = -sin(player->angle) * 0.66;
	player->plane.y = cos(player->angle) * 0.66;
}
