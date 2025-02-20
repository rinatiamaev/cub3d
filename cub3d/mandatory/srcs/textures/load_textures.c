/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 13:58:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_single_texture(t_game *game, t_texture *tex,
														char *path, void *mlx)
{
	tex->ptr = mlx_xpm_file_to_image(mlx, path, &tex->size.x, &tex->size.y);
	if (!tex->ptr)
		error(game, "mlx_xpm_file_to_image() failed");
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp,
			&tex->line_size, &tex->endian);
	if (!tex->addr)
		error(game, "mlx_get_data_addr() failed");
}

void	load_textures(t_game *game, t_conf conf)
{
	load_single_texture(game, &game->tex.no, conf.tex_no, game->mlx);
	load_single_texture(game, &game->tex.so, conf.tex_so, game->mlx);
	load_single_texture(game, &game->tex.we, conf.tex_we, game->mlx);
	load_single_texture(game, &game->tex.ea, conf.tex_ea, game->mlx);
}
