/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_kitty_npc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:03:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 20:38:50 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_texture	*get_npc_movement_texture(t_game *game, t_npc *npc)
{
	int	block;
	int	base_index;
	int	index;

	block = get_walk_block(npc, &game->player);
	base_index = get_walk_animation_base_index(block);
	index = base_index + (npc->sprite.anim_index % 4);
	if (index < 0 || index >= npc->sprite.move_frames_count)
		index = base_index;
	return (&npc->sprite.move_frames[index]);
}

static t_texture	*get_npc_wait_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.idle_frames_count)
		index = 0;
	return (&npc->sprite.idle_frames[index]);
}

static t_texture	*get_npc_speak_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.speak_frames_count)
		index = 0;
	return (&npc->sprite.speak_frames[index]);
}

static void	setup_temp_sprite(t_sprite *temp, t_npc *npc, t_texture *tex)
{
	ft_memset(temp, 0, sizeof(t_sprite));
	temp->pos = npc->pos;
	temp->size = npc->sprite.size;
	temp->idle_frames_count = 1;
	temp->idle_frames = tex;
}

void	draw_kitty_npc(t_game *game, t_npc *npc, double *z_buffer)
{
	t_texture	*tex;
	t_sprite	temp;

	tex = NULL;
	if (npc->state == WAIT)
		tex = get_npc_wait_texture(npc);
	else if (npc->state == PATROL)
		tex = get_npc_movement_texture(game, npc);
	else if (npc->state == FOLLOW)
		tex = get_npc_movement_texture(game, npc);
	else if (npc->state == SPEAK)
		tex = get_npc_speak_texture(npc);
	setup_temp_sprite(&temp, npc, tex);
	draw_sprite(game, game->player, &temp, z_buffer);
}
