/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:17:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/03 21:59:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Closes the game and frees all allocated resources.
 *
 * This function properly frees all memory and resources used by the game,
 * then exits the program with a success status.
 *
 * @param game Pointer to the game context.
 * @return Always returns SUCCESS (though not reached due to exit).
 */
static int	close_game(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (SUCCESS);
}

/**
 * @brief Handles key press events and triggers corresponding actions.
 *
 * This function updates the key state to true for valid keycodes and executes
 * specific game logic based on the pressed key. It manages toggling the
 * minimap('M'), initiating NPC following('F'), pausing the game('P'),
 * and handling interactions ('E').
 *
 * @param keycode The keycode of the pressed key.
 * @param game Pointer to the game context.
 * @return Always returns SUCCESS.
 */
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

/**
 * @brief Handles key release events by updating key state.
 *
 * This function sets the key state to false when a valid keycode is
 * released, allowing the game to properly track key input for movement
 * and actions.
 *
 * @param keycode The keycode of the released key.
 * @param game Pointer to the game context.
 * @return Always returns SUCCESS.
 */
static int	keyrelease_hook(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 66000)
		game->keys[keycode] = (false);
	return (SUCCESS);
}

/**
 * @brief Handles window focus change events.
 *
 * If the game is currently running and the window focus changes, this
 * function pauses the game. Helps prevent unwanted input when the window
 * loses focus.
 *
 * @param game Pointer to the game context.
 * @return Always returns SUCCESS.
 */
static int	focus_hook(t_game *game)
{
	if (game->state == RUNNING)
		pause_game(game);
	return (SUCCESS);
}

/**
 * @brief Sets up event hooks for handling user input and window events.
 *
 * This function registers various hooks using the MiniLibX library to handle
 * key presses/releases, focus changes, window close events, and the main
 * game loop execution.
 *
 * @param game Pointer to the game context.
 * @param window Pointer to the game window structure.
 */
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
