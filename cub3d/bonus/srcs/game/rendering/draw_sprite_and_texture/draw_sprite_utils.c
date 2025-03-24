/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:09:11 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 22:06:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	compute_sprite_transform(t_sprite_draw *data, t_player player)
{
	t_dpoint	rel;
	double		det;
	double		inv_det;

	rel = data->relative_position;
	det = compute_determinant(player);
	if (fabs(det) < 0.000001)
		return (false);
	inv_det = compute_inverse_determinant(det);
	data->transform.x = compute_transform_x(player, rel, inv_det);
	data->transform.y = compute_transform_y(player, rel, inv_det);
	return (is_sprite_in_front(data->transform.y));
}

static void	select_sprite_frame(t_sprite_draw *data, t_sprite *sprite)
{
	data->current_frame = get_current_frame(sprite->anim_start,
			sprite->idle_frames_count, 200.0);
	data->texture = &sprite->idle_frames[data->current_frame];
}

bool	init_sprite_draw_data(t_sprite_draw *data, t_player player,
															t_sprite *sprite)
{
	data->relative_position = get_direction_vector(player.pos, sprite->pos);
	if (!compute_sprite_transform(data, player))
		return (false);
	if (!calc_sprite_screen_coords(data))
		return (false);
	select_sprite_frame(data, sprite);
	return (true);
}
