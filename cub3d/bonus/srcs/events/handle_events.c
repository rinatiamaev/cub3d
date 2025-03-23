/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:17:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/23 16:42:46 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	close_game(t_game *game)
{
	stop_background_music();
	free_game(game);
	exit(EXIT_SUCCESS);
	return (SUCCESS);
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
		handle_interaction(game);
	else if (keycode == FOLLOW_PLAYER)
		make_closest_npc_follow(game, 2.0);
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
	if (game->state == RUNNING)
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
