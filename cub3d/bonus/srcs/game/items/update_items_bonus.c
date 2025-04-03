/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_items_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:12:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 09:57:35 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Updates the animation frame of a key item over time.
 *
 * This function advances the animation of the key item by incrementing the
 * animation index after a fixed delay. It loops back to the first frame
 * when the end of the animation is reached.
 *
 * @param item Pointer to the key item to animate.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
static void	play_key_animation(t_item *item, double delta_time)
{
	double	anim_speed;

	anim_speed = 100.0;
	item->sprite.anim_timer += delta_time * 1000.0;
	if (item->sprite.anim_timer >= anim_speed)
	{
		item->sprite.anim_timer -= anim_speed;
		item->sprite.anim_index++;
		if (item->sprite.anim_index >= item->sprite.idle_frames_count)
			item->sprite.anim_index = 0;
	}
}

/**
 * @brief Updates all items in the game world.
 *
 * Currently only key items have animations that are updated each frame.
 * For each key item, the animation frame is updated based on elapsed time.
 *
 * @param game Pointer to the game state containing the item list.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
void	update_items(t_game *game, double delta_time)
{
	t_item	*item;
	int		i;

	i = 0;
	while (i < game->item_count)
	{
		item = game->items[i];
		if (ft_strcmp(item->name, "key") == 0)
			play_key_animation(item, delta_time);
		i++;
	}
}
