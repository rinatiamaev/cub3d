/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_column.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:22:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 22:43:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_sprite_pixel(t_game *game, t_point screen_pos,
								t_texture *tex, t_point tex_pos)
{
	int	color;

	color = get_tex_color(tex, tex_pos.x, tex_pos.y);
	if (color != 42)
		put_pixel(&game->img, screen_pos.x, screen_pos.y, color);
}

static int	get_texture_y(int screen_y, int sprite_height, int texture_height)
{
	int	offset;
	int	texture_y;

	offset = (screen_y - WIN_H / 2 + sprite_height / 2) * 256;
	texture_y = ((offset * texture_height) / sprite_height) / 256;
	return (texture_y);
}

static bool	is_sprite_stripe_visible(t_sprite_draw *data, double *z_buffer)
{
	if (data->transform.y <= 0)
		return (false);
	if (data->stripe_x < 0 || data->stripe_x >= WIN_W)
		return (false);
	if (data->transform.y >= z_buffer[data->stripe_x])
		return (false);
	return (true);
}

static int	calc_tex_pixel_x(int stripe_x, int screen_x,
										int sprite_width, int texture_width)
{
	int	relative_x;

	relative_x = stripe_x - (-sprite_width / 2 + screen_x);
	return ((relative_x * texture_width) / sprite_width);
}

void	draw_sprite_column(t_game *game, t_sprite_draw *data, double *z_buffer)
{
	t_point	screen_pos;

	if (!is_sprite_stripe_visible(data, z_buffer))
		return ;
	data->tex_pixel.x = calc_tex_pixel_x(data->stripe_x, data->screen_x,
			data->width, data->texture->size.x);
	screen_pos.x = data->stripe_x;
	screen_pos.y = data->draw_start.y;
	while (screen_pos.y < data->draw_end.y)
	{
		data->tex_pixel.y = get_texture_y(screen_pos.y, data->height,
				data->texture->size.y);
		draw_sprite_pixel(game, screen_pos, data->texture, data->tex_pixel);
		screen_pos.y++;
	}
}
