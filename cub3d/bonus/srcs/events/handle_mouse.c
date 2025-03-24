/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:59:48 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 00:51:27 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	is_mouse_inside_window(t_mouse_data *m, t_window *window)
{
	return (m->position.x >= 0 && m->position.x < window->size.x
		&& m->position.y >= 0 && m->position.y < window->size.y);
}

static void	update_rotation_speed(t_mouse_data *m, t_game *game,
															t_window *window)
{
	m->delta_x = m->position.x - m->center.x;
	if (fabs(m->delta_x) > (window->size.x / 5)
		&& is_mouse_inside_window(m, window))
	{
		m->rotation_speed
			= m->delta_x * m->sensitivity * game->player.rot_speed;
	}
	else
	{
		m->rotation_speed *= 0.9;
		if (fabs(m->rotation_speed) < 0.0001)
			m->rotation_speed = 0.0;
	}
}

static void	apply_rotation(t_mouse_data *m, t_game *game)
{
	if (m->rotation_speed > 0)
		rotate_player_left(&game->player, m->rotation_speed);
	else if (m->rotation_speed < 0)
		rotate_player_right(&game->player, -m->rotation_speed);
}

void	handle_mouse_movement(t_game *game, t_window *window)
{
	static double	stored_rotation_speed;
	t_mouse_data	m;

	m.sensitivity = 0.000009;
	m.center.x = window->size.x >> 1;
	m.center.y = window->size.y >> 1;
	mlx_mouse_get_pos(game->mlx, window->ptr, &m.position.x, &m.position.y);
	m.rotation_speed = stored_rotation_speed;
	update_rotation_speed(&m, game, window);
	apply_rotation(&m, game);
	stored_rotation_speed = m.rotation_speed;
}
