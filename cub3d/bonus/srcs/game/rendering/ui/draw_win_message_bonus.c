/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_win_message_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:17:25 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 20:48:16 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Displays the main win message and initializes drawing position.
 *
 * This function clears the window and draws a centered "YOU WON" message
 * at the middle of the screen. It also sets the starting Y-position in
 * the provided `pos` struct for further text lines to be drawn below.
 *
 * @param game Pointer to the game state (includes window and render context).
 * @param pos Pointer to a `t_point` used to track the current draw position.
 */

static void	draw_win_title(t_game *game, t_point *pos)
{
	pos->y = game->window->size.y >> 1;
	pos->x = (game->window->size.x >> 1) - 60;
	mlx_clear_window(game->mlx, game->window->ptr);
	mlx_string_put(game->mlx, game->window->ptr, pos->x, pos->y, 0xFFFFFF,
		"CONGRATULATIONS, YOU WON!");
	pos->y += 30;
}

/**
 * @brief Displays the names of NPCs saved by the player.
 *
 * This function iterates through the NPC list and checks each for
 * `is_saved`. If an NPC was saved, their name is printed at the current
 * position and the Y position is incremented for the next line.
 *
 * @param game Pointer to the game state (includes NPC list).
 * @param pos Pointer to the current draw position (updated in-place).
 * @return true if any NPCs were saved, false otherwise.
 */

static bool	draw_saved_npcs(t_game *game, t_point *pos)
{
	bool	any_saved;
	int		i;

	i = 0;
	any_saved = false;
	while (i < game->npc_count)
	{
		if (game->npcs[i]->is_saved)
		{
			any_saved = true;
			mlx_string_put(game->mlx, game->window->ptr, pos->x, pos->y,
				0xFFFFFF, game->npcs[i]->name);
			pos->y += 20;
		}
		i++;
	}
	return (any_saved);
}

/**
 * @brief Displays a message based on whether any NPCs were saved.
 *
 * If at least one NPC was saved, a congratulatory message is shown.
 * Otherwise, a sad message is displayed indicating the player failed
 * to save anyone.
 *
 * @param game Pointer to the game state.
 * @param pos The current drawing position.
 * @param any_saved Whether any NPCs were marked as saved.
 */

static void	draw_outcome_message(t_game *game, t_point pos, bool any_saved)
{
	if (any_saved)
		mlx_string_put(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
			"have been saved from the labyrinth!");
	else
		mlx_string_put(game->mlx, game->window->ptr, pos.x, pos.y, 0xFFFFFF,
			"But you locked the kittens forever...");
}

/**
 * @brief Displays the exit instruction in the top-left corner.
 *
 * Draws the "Press 'ESC' to exit the game" message at a fixed position
 * near the top-left of the window.
 *
 * @param game Pointer to the game state.
 */

static void	draw_exit_instruction(t_game *game)
{
	mlx_string_put(game->mlx, game->window->ptr, 20, 20, 0xFFFFFF,
		"Press 'ESC' to exit the game");
}

/**
 * @brief Displays the full win screen with dynamic NPC outcome.
 *
 * This high-level function orchestrates the win screen by:
 * - Displaying the main title.
 * - Listing saved NPCs (if any).
 * - Showing a contextual message based on the outcome.
 * - Providing an exit instruction.
 *
 * All text is drawn using `mlx_string_put` with fixed or relative
 * positioning, and white color.
 *
 * @param game Pointer to the game state (includes NPCs and window).
 */
void	draw_win_message(t_game *game)
{
	t_point	pos;
	bool	any_saved;

	draw_win_title(game, &pos);
	any_saved = draw_saved_npcs(game, &pos);
	draw_outcome_message(game, pos, any_saved);
	draw_exit_instruction(game);
}
