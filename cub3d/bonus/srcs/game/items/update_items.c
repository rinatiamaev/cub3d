/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:12:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:14:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
