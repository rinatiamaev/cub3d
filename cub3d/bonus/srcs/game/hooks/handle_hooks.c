/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:17:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/09 15:45:44 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	advance_npc_dialogue(t_npc *npc)
{
	if (npc->is_talking)
	{
		npc->current_line++;
		if (npc->current_line >= npc->line_count)
		{
			npc->current_line = 0;
			npc->is_talking = false;
			npc->state = NPC_STATE_WAIT;
		}
	}
}

static bool	interact_with_npc(t_game *game)
{
	t_npc	*npc;
	int		i;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (ft_cab_dist_dpoint(game->player.pos, npc->pos) <= 2.0)
		{
			if (npc->state != NPC_STATE_SPEAK)
			{
				npc->state = NPC_STATE_SPEAK;
				npc->sprite.anim_index = 0;
				npc->sprite.anim_timer = 0.0;
				npc->is_talking = true;
				npc->current_line = 0;
			}
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	interact_with_door(t_game *game)
{
	t_door	*door;
	int		i;

	i = 0;
	while (i < game->door_count)
	{
		door = game->doors[i];
		if (ft_cab_dist_dpoint(game->player.pos, door->pos) <= 2.0)
		{
			if (door->state == DOOR_CLOSED)
				door->state = DOOR_OPENING;
			else if (door->state == DOOR_OPEN)
				door->state = DOOR_CLOSING;
			return (true);
		}
		i++;
	}
	return (false);
}

static int	keypress_hook(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 66000)
		game->keys[keycode] = true;
	if (keycode == ESC)
		close_game(game);
	else if (keycode == PAUSE)
		pause_game(game);
	else if (keycode == TOGGLE_MINIMAP)
		game->minimap_visible = !game->minimap_visible;
	else if (keycode == INTERACTION)
	{
		int i = 0;
		while (i < game->npc_count)
		{
			if (game->npcs[i]->is_talking)
			{
				advance_npc_dialogue(game->npcs[i]);
				return SUCCESS;
			}
			i++;
		}
		if (!interact_with_npc(game))
			interact_with_door(game);
	}
	else if (keycode == FOLLOW_PLAYER)
	{
		int i = 0;
		while (i < game->npc_count)
		{
			if (game->npcs[i]->state == NPC_STATE_FOLLOW)
				game->npcs[i]->state = NPC_STATE_WAIT; // Stop following if already in FOLLOW mode
			else
				game->npcs[i]->state = NPC_STATE_FOLLOW; // Start following player
			i++;
		}
	}
	return (SUCCESS);
}

static int	keyrelease_hook(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 66000)
		game->keys[keycode] = (false);
	return (SUCCESS);
}

static int	focus_hook(t_game *game)
{
	if (!game->is_paused)
		pause_game(game);
	return (SUCCESS);
}

void	handle_event_hooks(t_game *game, t_window *window)
{
	mlx_hook(window->ptr, KEYPRESS, KEYPRESS_MASK, keypress_hook, game);
	mlx_hook(window->ptr, KEYRELEASE, KEYRELEASE_MASK, keyrelease_hook, game);
	mlx_hook(window->ptr, FOCUS_OUT, FOCUS_CHANGE_MASK, focus_hook, game);
	mlx_hook(window->ptr, FOCUS_IN, FOCUS_CHANGE_MASK, focus_hook, game);
	mlx_hook(window->ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		close_game, game);
	mlx_hook(window->ptr, CONFIGURE_NOTIFY, STRUCTURE_NOTIFY_MASK,
		focus_hook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
