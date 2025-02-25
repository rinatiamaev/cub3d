/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/26 00:17:45 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_single_xpm(t_game *game, t_texture *tex, char *path, void *mlx)
{
    printf("Attempting to load XPM at path: %s\n", path);

    int width, height;
    tex->ptr = mlx_xpm_file_to_image(mlx, path, &width, &height);

    if (!tex->ptr)
        error(game, "mlx_xpm_file_to_image() failed (File path or OS resource limit?)");

    tex->size.x = width;
    tex->size.y = height;

    printf("Loaded XPM: %s -> Size: %d x %d\n", path, width, height);

    tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->line_size, &tex->endian);
    if (!tex->addr)
        error(game, "mlx_get_data_addr() failed");
}

void load_npc_frames(t_game *game, t_npc *npc)
{
	int i;

	npc->idle_frames = x_calloc(game, npc->num_frames, sizeof(t_texture));
	i = 0;
	while (i < npc->num_frames)
	{
		load_single_xpm(game, &npc->idle_frames[i], npc->paths[i], game->mlx);
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
