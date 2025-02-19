/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:28:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 14:35:37 by nlouis           ###   ########.fr       */
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
	if (game->txt.no.ptr)
		mlx_destroy_image(game->mlx, game->txt.no.ptr);
	if (game->txt.so.ptr)
		mlx_destroy_image(game->mlx, game->txt.so.ptr);
	if (game->txt.we.ptr)
		mlx_destroy_image(game->mlx, game->txt.we.ptr);
	if (game->txt.ea.ptr)
		mlx_destroy_image(game->mlx, game->txt.ea.ptr);
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
