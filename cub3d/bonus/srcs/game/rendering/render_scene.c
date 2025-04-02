/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 02:42:34 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	setup_framebuffer(t_game *game, double **z_buffer)
{
	*z_buffer = x_calloc(game, WIN_W, sizeof(double));
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_size, &game->img.endian);
	ft_memcpy(game->img.addr, game->bg_img.addr,
		WIN_W * WIN_H * (game->img.bpp / 8));
}

static void	render_world(t_game *game, double *z_buffer)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
		raycast(game, &ray, &x, z_buffer);
	draw_entities(game, z_buffer);
	draw_minimap(game);
}

static void	render_ui(t_game *game, double delta_time)
{
	draw_npc_dialogue(game);
	draw_follow_state(game);
	draw_bucket_state(game);
	draw_splash(game, &game->player, delta_time);
	draw_temp_message(game);
}

void	render_scene(t_game *game, double delta_time)
{
	double	*z_buffer;

	setup_framebuffer(game, &z_buffer);
	render_world(game, z_buffer);
	mlx_put_image_to_window(game->mlx, game->window->ptr, game->img.ptr, 0, 0);
	render_ui(game, delta_time);
	mlx_destroy_image(game->mlx, game->img.ptr);
	free(z_buffer);
}
