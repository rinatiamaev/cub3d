/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:18 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:33:16 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	rotate_player(t_player *player, double angle_delta)
{
	player->facing_angle = wrap_angle(player->facing_angle + angle_delta);
	player->facing_dir.x = cos(player->facing_angle);
	player->facing_dir.y = sin(player->facing_angle);
	player->view_plane.x = -sin(player->facing_angle) * FOV;
	player->view_plane.y = cos(player->facing_angle) * FOV;
}

void	rotate_player_left(t_player *player, double delta_time)
{
	double	angle_delta;

	angle_delta = player->rot_speed * delta_time;
	rotate_player(player, angle_delta);
}

void	rotate_player_right(t_player *player, double delta_time)
{
	double	angle_delta;

	angle_delta = -player->rot_speed * delta_time;
	rotate_player(player, angle_delta);
}
