/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:28:29 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 11:53:02 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Frees all memory and resources associated with the map.
 *
 * This function deallocates all components of the t_map structure:
 * 
 * - The raw file content (`file_content`) read from the map file.
 * - The parsed map layout (`map_layout`) used during gameplay.
 * - The 2D matrix (`matrix`) representing walls and walkable tiles.
 * - Texture paths for each wall direction (NO, SO, WE, EA).
 * - Finally, the t_map structure itself is freed.
 *
 * This function ensures that no memory leaks occur when the map is discarded.
 *
 * @param map Pointer to the t_map structure to be freed.
 */
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

/**
 * @brief Destroys the game window and frees the associated memory.
 *
 * This function clears and destroys the MiniLibX window (if it exists),
 * and then frees the memory allocated for the t_window structure.
 * 
 * The MiniLibX `mlx` context is required for proper cleanup of the window.
 *
 * @param window Pointer to the t_window structure to free.
 * @param mlx Pointer to the MiniLibX context used to create the window.
 */
static void	free_window(t_window *window, void *mlx)
{
	if (mlx && window->ptr)
	{
		mlx_clear_window(mlx, window->ptr);
		mlx_destroy_window(mlx, window->ptr);
	}
	free(window);
}

/**
 * @brief Destroys all loaded textures in the game using MiniLibX.
 *
 * This function checks and releases all images loaded into memory,
 * including:
 * 
 * - Wall textures (no, so, we, ea)
 * - Door textures (standard and exit door)
 * - UI texture (dialogue box)
 * 
 * If a texture is non-null (`ptr` exists), it is destroyed via
 * `mlx_destroy_image`.
 *
 * @param game Pointer to the game structure containing texture data.
 */
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

/**
 * @brief Frees all dynamically allocated memory and resources in the game.
 *
 * This function is responsible for cleaning up all allocated resources
 * before the program exits. It performs the following operations:
 * 
 * - Frees all splash animation frames of the player.
 * - Frees all NPCs and associated structures.
 * - Frees all game items.
 * - Frees the array of doors.
 * - Frees the global entity array.
 * - Frees the game map, including layout, matrix, and texture paths.
 * - Destroys the background image if allocated.
 * - Frees the game window and destroys the window via MiniLibX.
 * - Frees all wall, door, and UI textures loaded with MiniLibX.
 * - Destroys the MiniLibX display context.
 * - Frees the MiniLibX pointer.
 * - Frees the main game structure itself.
 *
 * This ensures a clean shutdown without memory leaks or dangling pointers.
 *
 * @param game Pointer to the game context to be deallocated.
 */
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
