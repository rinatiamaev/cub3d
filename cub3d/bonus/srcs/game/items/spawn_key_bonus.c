/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_key_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:50:36 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 09:59:40 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes the animation frames and properties for a key sprite.
 *
 * Sets the sprite's size, position, animation frame paths, and frame count.
 * Loads all animation frames into memory and records the animation start time.
 *
 * @param game Pointer to the game context.
 * @param sprite Pointer to the sprite structure to initialize.
 * @param pos Position of the key in world coordinates (centered in tile).
 */
static void	init_key_animation(t_game *game, t_sprite *sprite, t_dpoint pos)
{
	struct timeval	tv;
	static char		*idle_frames[] = {
		KEY00, KEY01, KEY02, KEY03, KEY04, KEY05, KEY06, KEY07, KEY08, KEY09,
		KEY10, KEY11, KEY12, KEY13, KEY14, KEY15, KEY16, KEY17, KEY18
	};

	sprite->size = (t_point){128, 128};
	sprite->pos = pos;
	sprite->idle_paths = idle_frames;
	sprite->idle_frames_count = sizeof(idle_frames) / sizeof(idle_frames[0]);
	load_sprite_animation(game, &sprite->idle_frames, sprite->idle_paths,
		sprite->idle_frames_count);
	set_frame_sizes
		(sprite->idle_frames, sprite->idle_frames_count, sprite->size);
	sprite->anim_index = 0;
	sprite->anim_timer = 0.0;
	gettimeofday(&tv, NULL);
	sprite->anim_start = tv.tv_sec * 1000000L + tv.tv_usec;
}

/**
 * @brief Initializes the key item with its basic properties.
 *
 * Sets the type, name, collectible status, and position of the key item.
 *
 * @param item Pointer to the item structure to initialize.
 * @param pos Position of the key in world coordinates (centered in tile).
 */
static void	init_key(t_item *item, t_dpoint pos)
{
	item->type = "animated";
	item->name = "key";
	item->is_collectible = true;
	item->pos = pos;
}

/**
 * @brief Spawns a key item into the game world with animation.
 *
 * Allocates and initializes a new key item at the specified tile position,
 * centers it in the tile, initializes its animation, and adds it to the item list.
 *
 * @param game Pointer to the game context.
 * @param x Tile-based x-coordinate for key placement.
 * @param y Tile-based y-coordinate for key placement.
 */
void	spawn_key(t_game *game, double x, double y)
{
	t_item		*item;
	t_dpoint	pos;

	item = x_calloc(game, 1, sizeof(t_item));
	pos = (t_dpoint){x + 0.5, y + 0.5};
	init_key(item, pos);
	init_key_animation(game, &item->sprite, pos);
	update_item_list(game, item);
}
