/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_win_condition_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:06 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:48:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Checks if the NPC is close to the exit door.
 *
 * Iterates over all doors in the game and finds the one marked as an
 * exit door (`EXIT_DOOR_TYPE`). If the NPC is within a specified distance
 * (`max_dist`) from that door, it is considered near the exit.
 *
 * Used to determine which NPCs have been saved when the player wins.
 *
 * @param npc Pointer to the NPC to check.
 * @param game Pointer to the game state (for access to doors).
 * @return true if the NPC is within range of the exit door, false otherwise.
 */
static bool	is_npc_near_exit(t_npc *npc, t_game *game)
{
	int				i;
	t_door			*door;
	const double	max_dist = 8.0;

	i = 0;
	while (i < game->door_count)
	{
		door = game->doors[i];
		if (door->type == EXIT_DOOR_TYPE)
		{
			if (ft_euclidean_dist_dpoint(npc->pos, door->pos) <= max_dist)
				return (true);
		}
		i++;
	}
	return (false);
}

/**
 * @brief Flags NPCs as saved if they are near the exit when the game is won.
 *
 * Called when the player reaches the exit. Iterates through all NPCs
 * and checks their proximity to the exit door. If close enough,
 * the NPC is marked as `is_saved = true`.
 *
 * This information is used to determine the outcome message upon winning.
 *
 * @param game Pointer to the game state.
 */
static void	update_saved_npcs(t_game *game)
{
	int	i;

	if (game->state != WIN)
		return ;
	i = 0;
	while (i < game->npc_count)
	{
		if (is_npc_near_exit(game->npcs[i], game))
			game->npcs[i]->is_saved = true;
		i++;
	}
}

/**
 * @brief Checks if the player has reached and opened the exit door.
 *
 * This function is called regularly to evaluate whether the player has
 * won the game. It checks:
 * - Whether the player's current tile is marked as an `EXIT_DOOR`.
 * - Whether the door at that position is in the `DOOR_OPEN` state.
 *
 * If both are true, the game state is set to `WIN`, and nearby NPCs
 * are evaluated and flagged as saved.
 *
 * @param game Pointer to the game state.
 */
void	check_win_condition(t_game *game)
{
	t_point	player_pos;
	t_door	*door;

	player_pos.x = (int)game->player.pos.x;
	player_pos.y = (int)game->player.pos.y;
	if (game->map->matrix[player_pos.y][player_pos.x] == EXIT_DOOR)
	{
		door = find_door_at(game, (t_point){player_pos.x, player_pos.y});
		if (door && door->state == DOOR_OPEN)
		{
			game->state = WIN;
			update_saved_npcs(game);
		}
	}
}
