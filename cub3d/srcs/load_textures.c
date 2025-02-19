/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 14:32:00 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_single_texture(t_game *game, t_texture *tex, char *path, void *mlx)
{
	tex->ptr = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->ptr)
		error(game, "mlx_xpm_file_to_image() failed");
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		error(game, "mlx_get_data_addr() failed");
}

void	load_textures(t_game *game, t_conf conf)
{
	load_single_texture(game, &game->txt.no, conf.text_no, game->mlx);
	load_single_texture(game, &game->txt.so, conf.text_so, game->mlx);
	load_single_texture(game, &game->txt.we, conf.text_we, game->mlx);
	load_single_texture(game, &game->txt.ea, conf.text_ea, game->mlx);
}
