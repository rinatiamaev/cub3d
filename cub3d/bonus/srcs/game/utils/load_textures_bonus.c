/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:25:33 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:45:48 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Loads a single XPM image into a texture structure.
 *
 * Uses MiniLibX to load an XPM file and populate a `t_texture` struct with
 * the resulting image pointer, dimensions, and pixel data.
 *
 * If loading fails at any point, an error is raised and the game exits.
 *
 * @param game Pointer to the game state (used for error handling).
 * @param tex Pointer to the texture to populate.
 * @param path Path to the XPM image file.
 * @param mlx MLX context used to load the image.
 */
void	load_single_xpm(t_game *game, t_texture *tex, char *path, void *mlx)
{
	int	width;
	int	height;

	tex->ptr = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!tex->ptr)
		error(game, "mlx_xpm_file_to_image() failed");
	tex->size.x = width;
	tex->size.y = height;
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->line_size,
			&tex->endian);
	if (!tex->addr)
		error(game, "mlx_get_data_addr() failed");
}

/**
 * @brief Loads a sequence of textures for sprite animation.
 *
 * Allocates memory for `frame_count` textures and loads each frame from
 * its corresponding file path using `load_single_xpm`.
 *
 * This function is used to prepare idle, move, speak, or hit animations.
 *
 * @param game Pointer to the game state (for allocation and error handling).
 * @param frames Address of the texture pointer array to populate.
 * @param paths Array of file paths for each animation frame.
 * @param frame_count Number of frames to load.
 */
void	load_sprite_animation(t_game *game, t_texture **frames,
	char **paths, int frame_count)
{
	int	i;

	*frames = x_calloc(game, frame_count, sizeof(t_texture));
	i = 0;
	while (i < frame_count)
	{
		load_single_xpm(game, &((*frames)[i]), paths[i], game->mlx);
		i++;
	}
}

/**
 * @brief Loads all animation frames for a given NPC sprite.
 *
 * This function loads all relevant animation sets for the NPC:
 * - Idle
 * - Movement
 * - Speaking
 * - (Optionally) Hit reaction
 *
 * Each set is loaded with `load_sprite_animation`, filling the sprite's
 * corresponding texture arrays.
 *
 * @param game Pointer to the game state.
 * @param sprite Pointer to the NPC sprite to initialize.
 */
void	load_sprite_frames_npc(t_game *game, t_sprite *sprite)
{
	load_sprite_animation(game, &sprite->idle_frames, sprite->idle_paths,
		sprite->idle_frames_count);
	load_sprite_animation(game, &sprite->move_frames, sprite->move_paths,
		sprite->move_frames_count);
	load_sprite_animation(game, &sprite->speak_frames, sprite->speak_paths,
		sprite->speak_frames_count);
	if (sprite->hit_paths)
		load_sprite_animation(game, &sprite->hit_frames, sprite->hit_paths,
			sprite->hit_frames_count);
}

/**
 * @brief Loads all base game textures from file.
 *
 * Loads wall textures (N/S/E/W), doors, exit doors, and the UI dialogue box.
 * Uses XPM image files defined in the map config and constants.
 *
 * @param game Pointer to the game state.
 * @param conf Configuration struct containing file paths for wall textures.
 */
void	load_game_textures(t_game *game, t_conf conf)
{
	load_single_xpm(game, &game->tex.no, conf.tex_no, game->mlx);
	load_single_xpm(game, &game->tex.so, conf.tex_so, game->mlx);
	load_single_xpm(game, &game->tex.we, conf.tex_we, game->mlx);
	load_single_xpm(game, &game->tex.ea, conf.tex_ea, game->mlx);
	load_single_xpm(game, &game->tex.door, SLIDING_DOOR, game->mlx);
	load_single_xpm(game, &game->tex.exit_door, DOOR_EXIT, game->mlx);
	load_single_xpm(game, &game->tex.dialogue_box, DIALOGUE_BOX, game->mlx);
}
