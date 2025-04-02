/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_follow_state_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:51:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 20:38:35 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Counts the number of NPCs currently following the player.
 *
 * Iterates over all NPCs in the game and counts those marked as
 * `is_following == true`.
 *
 * @param game Pointer to the game state containing the NPC list.
 * @return The number of NPCs actively following the player.
 */
static int	count_following_npcs(t_game *game)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < game->npc_count)
	{
		if (game->npcs[i]->is_following)
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief Generates a message based on the number of following NPCs.
 *
 * If only one NPC is following, it sets a fixed message.
 * Otherwise, it builds a dynamic message with the number of followers.
 *
 * The message is safely copied into the provided buffer `message`, using
 * `size` as the maximum allowed size to prevent overflow.
 *
 * @param game Pointer to the game state (used for memory-safe allocation).
 * @param following_count The number of NPCs currently following the player.
 * @param message Buffer to store the generated message.
 * @param size The size of the message buffer.
 */
static void	get_follow_message(t_game *game, int following_count,
										char *message, size_t size)
{
	char	*count_str;

	if (following_count == 1)
		ft_strlcpy(message, "You are followed by someone!", size);
	else
	{
		count_str = x_itoa(game, following_count);
		ft_strlcpy(message, "You are followed by ", size);
		ft_strlcat(message, count_str, size);
		ft_strlcat(message, " people!", size);
		free(count_str);
	}
}

/**
 * @brief Draws the follow message UI element to the game window.
 *
 * This function displays a fixed UI box near the top-right of the screen
 * and renders the provided message text inside it.
 *
 * It uses a predefined position and a static color for the text.
 *
 * @param game Pointer to the game state (provides window and textures).
 * @param message The text message to display in the follow state box.
 */
static void	draw_follow_message(t_game *game, char *message)
{
	int		x;
	int		y;
	int		color;

	x = (WIN_W - 220);
	y = 20;
	color = 43;
	mlx_put_image_to_window
		(game->mlx, game->window->ptr, game->tex.dialogue_box.ptr, x, y);
	mlx_string_put
		(game->mlx, game->window->ptr, x + 15, y + 35, color, message);
}

/**
 * @brief Displays a message if any NPCs are following the player.
 *
 * This function handles the full rendering logic for follow state display:
 * - Counts how many NPCs are following the player.
 * - If none, does nothing.
 * - Otherwise, generates an appropriate message and draws it to the screen.
 *
 * This gives feedback to the player that someone is following them.
 *
 * @param game Pointer to the game state.
 */
void	draw_follow_state(t_game *game)
{
	int		following_count;
	char	message[50];

	following_count = count_following_npcs(game);
	if (following_count == 0)
		return ;
	get_follow_message(game, following_count, message, sizeof(message));
	draw_follow_message(game, message);
}
