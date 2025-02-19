/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:18 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 13:26:17 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_player *player, double rot_speed)
{
	t_dpoint	prev_dir;
	t_dpoint	prev_plane;

	prev_dir = player->dir;
	prev_plane = player->plane;
	player->dir.x = prev_dir.x * cos(rot_speed) - prev_dir.y * sin(rot_speed);
	player->dir.y = prev_dir.x * sin(rot_speed) + prev_dir.y * cos(rot_speed);
	player->plane.x = prev_plane.x * cos(rot_speed)
		- prev_plane.y * sin(rot_speed);
	player->plane.y = prev_plane.x * sin(rot_speed)
		+ prev_plane.y * cos(rot_speed);
}

void	rotate_right(t_player *player, double rot_speed)
{
	rotate_left(player, -rot_speed);
}
