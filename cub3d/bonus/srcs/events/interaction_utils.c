/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:36:54 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/20 22:37:03 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_dpoint	normalize_vector(t_dpoint vec)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (len == 0)
		return ((t_dpoint){0, 0});
	return ((t_dpoint){vec.x / len, vec.y / len});
}

bool	is_facing_target(t_player *player, t_dpoint target_pos)
{
	t_dpoint	to_target;
	double		dot;

	to_target.x = target_pos.x - player->pos.x;
	to_target.y = target_pos.y - player->pos.y;
	to_target = normalize_vector(to_target);
	dot = get_dot_product(player->dir, to_target);
	return (dot >= DOT_FOV_THRESHOLD);
}
