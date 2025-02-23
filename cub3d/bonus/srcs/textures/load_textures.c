/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/21 15:12:40 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	load_textures_array(t_game *game, t_texture *tex_array, int n,
																char **paths)
{
	int	i;

	i = 0;
	while (i < n)
	{
		load_single_texture(game, &tex_array[i], paths[i], game->mlx);
		i++;
	}
}

void	load_walls(t_game *game, t_conf conf)
{
	load_single_texture(game, &game->tex.no, conf.tex_no, game->mlx);
	load_single_texture(game, &game->tex.so, conf.tex_so, game->mlx);
	load_single_texture(game, &game->tex.we, conf.tex_we, game->mlx);
	load_single_texture(game, &game->tex.ea, conf.tex_ea, game->mlx);
}
