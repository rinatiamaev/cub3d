/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:05:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:21:19 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	t_door	*door;

	if (ray->hit == 2)
	{
		door = find_door_at(game, ray->map);
		if (door && door->type == EXIT_DOOR_TYPE)
			return (&game->tex.exit_door);
		return (&game->tex.door);
	}
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (&game->tex.ea);
		else
			return (&game->tex.we);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->tex.so);
		else
			return (&game->tex.no);
	}
}

static inline int	get_tex_color_no_alpha(t_texture *tex, int x, int y)
{
	unsigned int	*pixel_ptr;
	unsigned int	color;

	pixel_ptr
		= (unsigned int *)(tex->addr + y
			* tex->line_size + x * (tex->bpp >> 3));
	color = *pixel_ptr;
	return (color);
}

void	draw_wall_column(t_game *game, t_ray *ray, int *x)
{
	t_texture	*tex;
	int			y;
	char		*dst;
	int			color;

	tex = select_wall_texture(game, ray);
	y = ray->draw_start;
	dst = game->img.addr + (y * game->img.line_size)
		+ ((*x) * (game->img.bpp >> 3));
	while (y <= ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (tex->size.y - 1);
		ray->tex_pos += ray->step;
		color = get_tex_color_no_alpha(tex, ray->tex.x, ray->tex.y);
		*(unsigned int *)dst = color;
		dst += game->img.line_size;
		y++;
	}
}

void	raycast(t_game *game, t_ray *ray, int *x, double *z_buffer)
{
	init_ray(game, ray, *x);
	init_dda_ray(game, ray);
	perform_dda(game, ray);
	calculate_ray_properties(game, ray);
	draw_wall_column(game, ray, x);
	z_buffer[(*x)++] = ray->perp_w_dist;
}
