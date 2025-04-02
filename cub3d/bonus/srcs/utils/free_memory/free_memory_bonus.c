/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:28:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 19:37:32 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_map(t_map *map)
{
	ft_free_array((void **)map->file_content);
	ft_free_array((void **)map->map_layout);
	ft_free_matrix(map->matrix, map->size.y);
	free(map->conf.tex_no);
	free(map->conf.tex_so);
	free(map->conf.tex_we);
	free(map->conf.tex_ea);
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
	if (game->tex.no.ptr)
		mlx_destroy_image(game->mlx, game->tex.no.ptr);
	if (game->tex.so.ptr)
		mlx_destroy_image(game->mlx, game->tex.so.ptr);
	if (game->tex.we.ptr)
		mlx_destroy_image(game->mlx, game->tex.we.ptr);
	if (game->tex.ea.ptr)
		mlx_destroy_image(game->mlx, game->tex.ea.ptr);
	if (game->tex.door.ptr)
		mlx_destroy_image(game->mlx, game->tex.door.ptr);
	if (game->tex.exit_door.ptr)
		mlx_destroy_image(game->mlx, game->tex.exit_door.ptr);
	if (game->tex.dialogue_box.ptr)
		mlx_destroy_image(game->mlx, game->tex.dialogue_box.ptr);
}

void	free_game(t_game *game)
{
	free_tex_frames(game, game->player.sprite.splash_frames,
		game->player.sprite.splash_frames_count);
	free_npcs(game);
	free_items(game);
	ft_free_array_size((void **)game->doors, game->door_count);
	free(game->entities);
	free_map(game->map);
	if (game->bg_img.ptr)
		mlx_destroy_image(game->mlx, game->bg_img.ptr);
	if (game->window)
		free_window(game->window, game->mlx);
	free_textures(game);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}
