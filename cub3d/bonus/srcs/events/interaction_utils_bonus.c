/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:36:54 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 00:54:04 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_facing_target(t_player *player, t_dpoint target_pos)
{
	t_dpoint	target_dir;
	double		dot;
	double		fov_threshold;

	target_dir = get_unit_direction_vector(player->pos, target_pos);
	dot = get_dot_product(player->facing_dir, target_dir);
	fov_threshold = FOV_THRESHOLD;
	return (dot >= fov_threshold);
}
