/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:28:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 09:41:54 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	ft_free_array((void **)map->file_content);
	ft_free_array((void **)map->map_layout);
	ft_free_matrix(map->matrix, map->row_count);
	free(map->conf.text_no);
	free(map->conf.text_so);
	free(map->conf.text_we);
	free(map->conf.text_ea);
	free(map);
}

static void	free_window(t_window *window, void *mlx)
{
	if (mlx && window->ptr)
	{
		mlx_clear_window(mlx, window->ptr);
		mlx_destroy_window(mlx, window->ptr);
	}
	free(window);
}

static void	free_textures(t_game *game)
{
	if (game->img.no_wall)
		mlx_destroy_image(game->mlx, game->img.no_wall);
	if (game->img.so_wall)
		mlx_destroy_image(game->mlx, game->img.so_wall);
	if (game->img.we_wall)
		mlx_destroy_image(game->mlx, game->img.we_wall);
	if (game->img.ea_wall)
		mlx_destroy_image(game->mlx, game->img.ea_wall);
}

void	free_game(t_game *game)
{
	free_map(game->map);
	if (game->window)
		free_window(game->window, game->mlx);
	free_textures(game);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}
