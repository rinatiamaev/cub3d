/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_column.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:22:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:18:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	get_texture_y(int screen_y, int sprite_height,
															int texture_height)
{
	int		offset;
	int		texture_y;

	offset = screen_y - (WIN_H >> 1) + (sprite_height >> 1);
	offset = (int)(((int64_t)offset) << 8);
	texture_y
		= (int)((((int64_t)offset * texture_height) / sprite_height) >> 8);
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

static inline unsigned int	get_tex_color(t_texture *tex, int x, int y)
{
	unsigned int	*pixel_ptr;
	unsigned int	color;

	if (x < 0 || x >= tex->size.x || y < 0 || y >= tex->size.y)
		return (42);
	pixel_ptr
		= (unsigned int *)(tex->addr + y
			* tex->line_size + x * (tex->bpp >> 3));
	color = *pixel_ptr;
	if ((color & 0x00FFFFFF) == 0x000000)
		return (42);
	return (color);
}

void	draw_sprite_column(t_game *game, t_sprite_draw *data, double *z_buffer)
{
	t_point			screen_pos;
	char			*dst;
	unsigned int	color;

	if (!is_sprite_stripe_visible(data, z_buffer))
		return ;
	data->tex_pixel.x = calc_tex_pixel_x(data->stripe_x, data->screen_x,
			data->width, data->texture->size.x);
	screen_pos.x = data->stripe_x;
	screen_pos.y = data->draw_start.y;
	dst = game->img.addr + (screen_pos.y * game->img.line_size)
		+ (screen_pos.x * (game->img.bpp >> 3));
	while (screen_pos.y < data->draw_end.y)
	{
		data->tex_pixel.y = get_texture_y(screen_pos.y, data->height,
				data->texture->size.y);
		color
			= get_tex_color
			(data->texture, data->tex_pixel.x, data->tex_pixel.y);
		if ((color & 0x00FFFFFF) != 42)
			*(unsigned int *)dst = color;
		dst += game->img.line_size;
		screen_pos.y++;
	}
}
