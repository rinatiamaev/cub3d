/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 09:40:09 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_wall_textures(t_game *game, t_img *img, t_conf conf, void *mlx)
{
	t_point	size;

	size = (t_point){TEXT_W, TEXT_H};
	img->no_wall = mlx_xpm_file_to_image(mlx, conf.text_no, &size.x, &size.y);
	img->so_wall = mlx_xpm_file_to_image(mlx, conf.text_so, &size.x, &size.y);
	img->we_wall = mlx_xpm_file_to_image(mlx, conf.text_we, &size.x, &size.y);
	img->ea_wall = mlx_xpm_file_to_image(mlx, conf.text_ea, &size.x, &size.y);
	if (!img->no_wall || !img->so_wall || !img->we_wall || !img->ea_wall)
		error(game, "mlx_xpm_file_to_image() failed");
}

void	load_textures(t_game *game)
{
	load_wall_textures(game, &game->img, game->map->conf, game->mlx);
}