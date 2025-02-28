/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:28:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/28 12:39:03 by nlouis           ###   ########.fr       */
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
}

static void	free_npcs(t_game *game)
{
	t_npc	*npc;
	int			i;
	int			j;

	if (!game->npcs)
		return ;
	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (npc)
		{
			j = 0;
			while (j < npc->sprite.num_idle_frames)
			{
				if (npc->sprite.idle_frames[j].ptr)
					mlx_destroy_image(game->mlx, npc->sprite.idle_frames[j].ptr);
				j++;
			}
			free(npc->sprite.idle_frames);
			free(npc);
		}
		i++;
	}
	free(game->npcs);
}

void	free_game(t_game *game)
{
	free_npcs(game);
	free_map(game->map);
	if (game->window)
		free_window(game->window, game->mlx);
	free_textures(game);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}
