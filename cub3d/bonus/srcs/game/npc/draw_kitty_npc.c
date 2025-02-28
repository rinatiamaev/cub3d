/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_kitty_npc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:03:59 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/01 01:19:45 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_walk_block(t_npc *npc, t_player *player)
{
	double		angle_move;
	t_dpoint	delta;
	double		angle_player;
	double		diff;
	double		deg;

	angle_move = atan2(npc->move_vec.y, npc->move_vec.x);
	delta = (t_dpoint){player->pos.x - npc->pos.x, player->pos.y - npc->pos.y};
	angle_player = atan2(delta.y, delta.x);
	diff = angle_move - angle_player;
	while (diff < -M_PI)
		diff += 2 * M_PI;
	while (diff > M_PI)
		diff -= 2 * M_PI;
	deg = diff * (180.0 / M_PI);
	if (deg < 0)
		deg += 360.0;
	if ((deg >= 315 && deg < 360) || (deg >= 0 && deg < 45))
		return (WALK_TOWARD);
	else if (deg >= 45 && deg < 135)
		return (WALK_LEFT);
	else if (deg >= 135 && deg < 225)
		return (WALK_AWAY);
	else
		return (WALK_RIGHT);
}

static t_texture	*get_npc_movement_texture(t_game *game, t_npc *npc)
{
	int	block;
	int	base_index;
	int	index;

	block = get_walk_block(npc, &game->player);
	base_index = 0;
	if (block == WALK_AWAY)
		base_index = 0;
	else if (block == WALK_TOWARD)
		base_index = 4;
	else if (block == WALK_LEFT)
		base_index = 8;
	else
		base_index = 12;
	index = base_index + npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.move_frames_count)
		index = 0;
	return (&npc->sprite.move_frames[index]);
}

static t_texture	*get_npc_wait_texture(t_npc *npc)
{
	int	index;

	index = npc->sprite.anim_index;
	if (index < 0 || index >= npc->sprite.num_idle_frames)
		index = 0;
	return (&npc->sprite.idle_frames[index]);
}

static void	setup_temp_sprite(t_sprite *temp, t_npc *npc, t_texture *tex)
{
	ft_memset(temp, 0, sizeof(t_sprite));
	temp->pos = npc->pos;
	temp->size = npc->sprite.size;
	temp->num_idle_frames = 1;
	temp->idle_frames = tex;
	temp->type = npc->sprite.type;
}

void	draw_kitty_npc(t_game *game, t_npc *npc, double *z_buffer)
{
	t_texture	*tex;
	t_sprite	temp;

	if (npc->state == NPC_STATE_WAIT)
		tex = get_npc_wait_texture(npc);
	else if (npc->state == NPC_STATE_PATROL)
		tex = get_npc_movement_texture(game, npc);
	setup_temp_sprite(&temp, npc, tex);
	draw_sprite(game, game->player, &temp, z_buffer);
}
