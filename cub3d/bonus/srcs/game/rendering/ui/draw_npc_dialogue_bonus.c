/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc_dialogue_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:58:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 20:56:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Determines if an NPC's dialogue should be displayed.
 *
 * This function performs multiple checks to ensure that an NPC is eligible
 * to display dialogue:
 *
 * - The NPC must be in the `SPEAK` state.
 * - The dialogue phase must be within valid bounds (0–9).
 * - The dialogue data for the current phase must not be null.
 * - The current dialogue line index must be valid. If it's out of bounds,
 *   it is reset to 0 as a safety fallback.
 *
 * This function prevents accessing invalid dialogue data and avoids drawing
 * incomplete or erroneous UI elements.
 *
 * @param npc Pointer to the NPC whose dialogue state is being checked.
 * @return true if the NPC's dialogue should be rendered, false otherwise.
 */
static bool	should_draw_npc_dialogue(t_npc *npc)
{
	if (npc->state != SPEAK)
		return (false);
	if (npc->dialogue.phase < 0 || npc->dialogue.phase >= 10)
		return (false);
	if (!npc->dialogue.dialogues[npc->dialogue.phase])
		return (false);
	if (npc->dialogue.current_line < 0
		|| npc->dialogue.current_line
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
		npc->dialogue.current_line = 0;
	return (true);
}

/**
 * @brief Retrieves the current line of dialogue for an NPC.
 *
 * This function returns the dialogue string corresponding to the NPC's
 * current phase and dialogue line index. If the current line index exceeds
 * the number of lines in the current phase, it resets the index to 0 to
 * prevent out-of-bounds access.
 *
 * This function assumes the phase is already validated (e.g. by
 * `should_draw_npc_dialogue`) and is used to fetch the string for rendering.
 *
 * @param npc Pointer to the NPC whose dialogue is being accessed.
 * @return The current dialogue line as a null-terminated string.
 */
static char	*get_current_dialogue_line(t_npc *npc)
{
	if (npc->dialogue.current_line
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
		npc->dialogue.current_line = 0;
	return (npc->dialogue.dialogues
		[npc->dialogue.phase][npc->dialogue.current_line]);
}

/**
 * @brief Renders the current dialogue line of a speaking NPC.
 *
 * This function displays a dialogue box on screen and prints the current
 * dialogue line of the given NPC. The dialogue is centered horizontally and
 * placed near the bottom of the screen.
 *
 * It uses:
 * - `get_current_dialogue_line()` to retrieve the dialogue text.
 * - `mlx_put_image_to_window()` to draw the dialogue background.
 * - `mlx_string_put()` to render the text inside the box.
 *
 * If no valid text is found, nothing is rendered.
 *
 * @param game Pointer to the game state (provides rendering context).
 * @param npc Pointer to the NPC whose dialogue should be rendered.
 */
void	render_npc_dialogue(t_game *game, t_npc *npc)
{
	int		x;
	int		y;
	int		color;
	char	*dialogue_text;

	x = ((WIN_W >> 1) - 128);
	y = (WIN_H - (WIN_H / 5));
	color = 43;
	dialogue_text = get_current_dialogue_line(npc);
	if (!dialogue_text)
		return ;
	mlx_put_image_to_window(game->mlx, game->window->ptr,
		game->tex.dialogue_box.ptr, x, y);
	mlx_string_put
		(game->mlx, game->window->ptr, x + 15, y + 35, color, dialogue_text);
}

/**
 * @brief Iterates through NPCs and renders active dialogue.
 *
 * This function checks each NPC in the game to determine whether they are
 * currently in a speaking state and have valid dialogue. If so, their
 * dialogue is rendered on the screen via `render_npc_dialogue`.
 *
 * It relies on `should_draw_npc_dialogue()` for safety checks and
 * avoids rendering dialogue for NPCs that are inactive or out of bounds.
 *
 * @param game Pointer to the game state (contains NPCs and render context).
 */
void	draw_npc_dialogue(t_game *game)
{
	int		i;
	t_npc	*npc;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (should_draw_npc_dialogue(npc))
			render_npc_dialogue(game, npc);
		i++;
	}
}
