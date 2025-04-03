/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:38:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 10:01:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes the splash animation frames for the player.
 *
 * Loads a sequence of full-screen splash textures used for displaying
 * animated effects (water splash). These are assigned to the player's
 * sprite structure and will be used when `is_splashing` is active.
 *
 * @param game Pointer to the game context.
 * @param player Pointer to the player.
 * @param sprite Pointer to the player's sprite data to store splash frames.
 */
static void	init_splash_animation(t_game *game, t_player *player,
															t_sprite *sprite)
{
	static char	*splash_frames[] = {
		SPLASH_1, SPLASH_2, SPLASH_3, SPLASH_4, SPLASH_5, SPLASH_6, SPLASH_7
	};

	player->sprite.size = (t_point){WIN_W, WIN_H};
	player->sprite.splash_paths = splash_frames;
	player->sprite.splash_frames_count
		= sizeof(splash_frames) / sizeof(char *);
	player->sprite.anim_index = 0;
	player->sprite.anim_timer = 0.0;
	load_sprite_animation(game, &sprite->splash_frames, sprite->splash_paths,
		sprite->splash_frames_count);
}

/**
 * @brief Sets the player's facing angle based on the map configuration.
 *
 * Converts the character representing the direction (`N`, `S`, `E`, `W`)
 * into a corresponding angle in radians, used to determine the direction
 * the player is initially looking at.
 *
 * @param player Pointer to the player.
 */
static void	set_player_facing_angle(t_player *player)
{
	if (player->conf_dir == 'N')
		player->facing_angle = 3 * M_PI / 2;
	else if (player->conf_dir == 'S')
		player->facing_angle = M_PI / 2;
	else if (player->conf_dir == 'W')
		player->facing_angle = M_PI;
	else if (player->conf_dir == 'E')
		player->facing_angle = 0;
}

/**
 * @brief Calculates and sets the player's direction and camera plane.
 *
 * Uses the player's facing angle to derive the direction vector and
 * view plane vector (used for raycasting field of view).
 *
 * @param player Pointer to the player.
 */
static void	set_player_direction_and_view_plane(t_player *player)
{
	player->facing_dir.x = cos(player->facing_angle);
	player->facing_dir.y = sin(player->facing_angle);
	player->view_plane.x = -sin(player->facing_angle) * FOV;
	player->view_plane.y = cos(player->facing_angle) * FOV;
}

/**
 * @brief Initializes the player's position, movement parameters and visuals.
 *
 * Centers the player in the map tile, sets rotation/movement speed,
 * initializes direction and camera plane based on config, and loads
 * the splash animation textures.
 *
 * @param game Pointer to the game context.
 * @param player Pointer to the player to initialize.
 */
void	init_player(t_game *game, t_player *player)
{
	player->pos.x += 0.5;
	player->pos.y += 0.5;
	player->rot_speed = 5;
	player->move_speed = 3;
	set_player_facing_angle(player);
	set_player_direction_and_view_plane(player);
	init_splash_animation(game, player, &player->sprite);
}
