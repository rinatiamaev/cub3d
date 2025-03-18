/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 09:35:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_scene(t_game *game, double delta_time)
{
	t_ray	ray;
	int		x;
	double	*z_buffer;

	z_buffer = x_calloc(game, WIN_W, sizeof(double));
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.line_size, &game->img.endian);
	fill_ceiling_and_floor(&game->img, game->map->conf.ceiling_color,
		game->map->conf.floor_color);
	x = 0;
	while (x < WIN_W)
		raycast(game, &ray, &x, z_buffer);
	draw_npcs(game, z_buffer);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window->ptr, game->img.ptr, 0, 0);
	draw_npc_dialogue(game);
	draw_follow_state(game);
	draw_splash(game, &game->player, delta_time);
	mlx_destroy_image(game->mlx, game->img.ptr);
	free(z_buffer);
}
