/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/26 14:59:03 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_single_xpm(t_game *game, t_texture *tex, char *path, void *mlx)
{
    int	width;
	int	height;
	
    tex->ptr = mlx_xpm_file_to_image(mlx, path, &width, &height);
    if (!tex->ptr)
        error(game, "mlx_xpm_file_to_image() failed (File path or OS resource limit?)");
    tex->size.x = width;
    tex->size.y = height;
    tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->line_size, &tex->endian);
    if (!tex->addr)
        error(game, "mlx_get_data_addr() failed");
}

void load_sprite_frames(t_game *game, t_sprite *sprite)
{
	int i;

	sprite->idle_frames = x_calloc(game, sprite->num_frames, sizeof(t_texture));
	i = 0;
	while (i < sprite->num_frames)
	{
		load_single_xpm(game, &sprite->idle_frames[i], sprite->paths[i], game->mlx);
		i++;
	}
}

void	load_walls_texture(t_game *game, t_conf conf)
{
	load_single_xpm(game, &game->tex.no, conf.tex_no, game->mlx);
	load_single_xpm(game, &game->tex.so, conf.tex_so, game->mlx);
	load_single_xpm(game, &game->tex.we, conf.tex_we, game->mlx);
	load_single_xpm(game, &game->tex.ea, conf.tex_ea, game->mlx);
}
