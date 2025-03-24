/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_sprite_transform_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:18:36 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:15:53 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	compute_determinant(t_player player)
{
	return (player.view_plane.x * player.facing_dir.y
		- player.facing_dir.x * player.view_plane.y);
}

double	compute_inverse_determinant(double det)
{
	return (1.0 / det);
}

double	compute_transform_x(t_player player, t_dpoint rel, double inv_det)
{
	return (inv_det * (player.facing_dir.y * rel.x
			- player.facing_dir.x * rel.y));
}

double	compute_transform_y(t_player player, t_dpoint rel, double inv_det)
{
	return (inv_det * (-player.view_plane.y * rel.x
			+ player.view_plane.x * rel.y));
}

bool	is_sprite_in_front(double transform_y)
{
	return (transform_y > 0.001);
}
