/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite_screen_coords.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:42:27 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:16:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_sprite_screen_x(double transform_x, double transform_y)
{
	int	screen_center_x;

	screen_center_x = WIN_W >> 1;
	return ((int)(screen_center_x * (1 + transform_x / transform_y)));
}

static int	get_sprite_scaled_dimension(double transform_y)
{
	int	scaled_height;

	scaled_height = (int)fabs(WIN_H / transform_y);
	return (fmax(scaled_height, 1));
}

static t_point	get_vertical_bounds(int height)
{
	t_point	vertical_bounds;

	vertical_bounds.y = clamp((WIN_H + height) / 2, 0, WIN_H - 1);
	vertical_bounds.x = clamp((WIN_H - height) / 2, 0, WIN_H - 1);
	return (vertical_bounds);
}

static t_point	get_horizontal_bounds(int screen_x, int width)
{
	t_point	horizontal_bounds;

	horizontal_bounds.x = clamp(screen_x - width / 2, 0, WIN_W - 1);
	horizontal_bounds.y = clamp(screen_x + width / 2, 0, WIN_W - 1);
	return (horizontal_bounds);
}

bool	calc_sprite_screen_coords(t_sprite_draw *data)
{
	t_point	vertical;
	t_point	horizontal;

	data->screen_x = get_sprite_screen_x(data->transform.x, data->transform.y);
	data->width = get_sprite_scaled_dimension(data->transform.y);
	data->height = data->width;
	vertical = get_vertical_bounds(data->height);
	horizontal = get_horizontal_bounds(data->screen_x, data->width);
	data->draw_start.y = vertical.x;
	data->draw_end.y = vertical.y;
	data->draw_start.x = horizontal.x;
	data->draw_end.x = horizontal.y;
	return (data->draw_start.x < data->draw_end.x
		&& data->draw_start.y < data->draw_end.y);
}
