/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:36:54 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 22:07:31 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if the player is facing a target position within a threshold.
 *
 * This function calculates the normalized direction from the player to the
 * target and uses the dot product between this direction and the player's
 * facing direction to determine if the target is within the player's
 * field of view (FOV).
 *
 * @param player Pointer to the player structure.
 * @param target_pos The position of the target to check.
 * @return true if the player is facing the target (dot product above
 *         FOV_THRESHOLD), false otherwise.
 */
bool	is_facing_target(t_player *player, t_dpoint target_pos)
{
	t_dpoint	target_dir;
	double		dot;

	target_dir = get_unit_direction_vector(player->pos, target_pos);
	dot = get_dot_product(player->facing_dir, target_dir);
	return (dot >= FOV_THRESHOLD);
}
