/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:17:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 22:54:12 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_pause_message(t_game *game)
{
	t_point	pos;

	pos.x = game->window->size.x / 2;
	pos.y = game->window->size.y / 2;
	mlx_string_put(game->mlx, game->window->ptr, pos.x, pos.y,
		0xFFFFFF, "PAUSED");
}

static int	pause_game(t_game *game)
{
	game->is_paused = !game->is_paused;
	mlx_clear_window(game->mlx, game->window->ptr);
	if (game->is_paused)
		draw_pause_message(game);
	return (SUCCESS);
}

static int	keypress_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	else if (keycode == PAUSE)
		pause_game(game);
	else if (!game->is_paused)
	{
		if (keycode == UP)
			move_forward(&game->player, game->map, game->player.move_speed);
		else if (keycode == DOWN)
			move_backward(&game->player, game->map, game->player.move_speed);
		else if (keycode == LEFT)
			strafe_left(&game->player, game->map, game->player.move_speed);
		else if (keycode == RIGHT)
			strafe_right(&game->player, game->map, game->player.move_speed);
		else if (keycode == ARR_RIGHT)
			rotate_right(&game->player, game->player.rot_speed);
		else if (keycode == ARR_LEFT)
			rotate_left(&game->player, game->player.rot_speed);
	}
	return (SUCCESS);
}

static int	resize_and_focus_hook(t_game *game)
{
	if (!game->is_paused)
		pause_game(game);
	return (SUCCESS);
}

void	handle_event_hooks(t_game *game, t_window *window)
{
	mlx_hook(window->ptr, KEYPRESS, KEYPRESS_MASK, keypress_hook, game);
	mlx_hook(window->ptr, FOCUS_OUT, FOCUS_CHANGE_MASK,
		resize_and_focus_hook, game);
	mlx_hook(window->ptr, FOCUS_IN, FOCUS_CHANGE_MASK,
		resize_and_focus_hook, game);
	mlx_hook(window->ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		close_game, game);
	mlx_hook(window->ptr, CONFIGURE_NOTIFY, STRUCTURE_NOTIFY_MASK,
		resize_and_focus_hook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
