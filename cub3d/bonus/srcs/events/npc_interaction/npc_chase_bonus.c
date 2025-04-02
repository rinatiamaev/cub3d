/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_chase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:16:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 19:58:54 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	trigger_splash_animation(t_player *player)
{
	player->is_splashing = true;
	player->sprite.anim_index = 0;
	player->sprite.anim_timer = 0.0;
}

bool	handle_npc_chase(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 4.0);
	if (npc && npc->state == CHASE
		&& game->player.has_water)
	{
		npc->is_hit = true;
		game->player.has_water = false;
		trigger_splash_animation(&game->player);
		return (false);
	}
	return (true);
}
