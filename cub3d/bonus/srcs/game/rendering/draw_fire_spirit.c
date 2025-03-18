/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fire_spirit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:32:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/17 20:08:26 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_texture	*get_npc_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.idle_frames_count)
		index = 0;
	return (&npc->sprite.idle_frames[index]);
}

static t_texture	*get_hit_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.hit_frames_count)
		index = 0;
	return (&npc->sprite.hit_frames[index]);
}

static void	setup_temp_sprite(t_sprite *temp, t_npc *npc, t_texture *tex)
{
	ft_memset(temp, 0, sizeof(t_sprite));
	temp->pos = npc->pos;
	temp->size = npc->sprite.size;
	temp->idle_frames_count = 1;
	temp->idle_frames = tex;
}

void	draw_fire_spirit(t_game *game, t_npc *npc, double *z_buffer)
{
	t_texture	*tex;
	t_sprite	temp;

	if (npc->is_enemy && npc->state == HIT)
		tex = get_hit_texture(npc);
	else
		tex = get_npc_texture(npc);
	setup_temp_sprite(&temp, npc, tex);
	draw_sprite(game, game->player, &temp, z_buffer);
}
