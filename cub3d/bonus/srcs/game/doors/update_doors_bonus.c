/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_doors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:02:28 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 22:14:14 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Gradually opens a door over time until it is fully open.
 *
 * Increases the door's opening offset based on its configured speed and the
 * elapsed time since the last frame. Once the door is fully open (offset ≥ 1),
 * its state is set to `DOOR_OPEN` and a timer is initialized to control how
 * long it stays open before closing again.
 *
 * @param door Pointer to the door being updated.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
static void	open_door(t_door *door, double delta_time)
{
	door->offset += door->speed * delta_time;
	if (door->offset >= 1.0)
	{
		door->offset = 1.0;
		door->state = DOOR_OPEN;
		door->open_timer = 1.5;
	}
}

/**
 * @brief Checks if any entity (player or NPC) is currently on the door tile.
 *
 * This function verifies whether the player's or any NPC's current position
 * matches the tile position of the specified door. It uses integer casting to
 * compare positions based on tile coordinates rather than exact floating-point
 * locations.
 *
 * @param game Pointer to the game state, containing player and NPC data.
 * @param door Pointer to the door to check.
 * @return true if the player or any NPC is on the door's tile, false otherwise
 */
static bool	is_entity_on_door(t_game *game, t_door *door)
{
	int	i;

	if ((int)game->player.pos.x == (int)door->pos.x
		&& (int)game->player.pos.y == (int)door->pos.y)
		return (true);
	i = 0;
	while (i < game->npc_count)
	{
		if ((int)game->npcs[i]->pos.x == (int)door->pos.x
			&& (int)game->npcs[i]->pos.y == (int)door->pos.y)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Handles the closing animation and logic of a door.
 *
 * If any entity (player or NPC) is currently on the door, it interrupts the
 * closing process and reopens the door, resetting the open timer.
 * Otherwise, the door continues closing based on its speed and the frame's
 * delta time. Once fully closed, its state is set to DOOR_CLOSED and the
 * offset is clamped to 0.
 *
 * @param game Pointer to the game state, used to check entity positions.
 * @param door Pointer to the door being updated.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
static void	close_door(t_game *game, t_door *door, double delta_time)
{
	if (is_entity_on_door(game, door))
	{
		door->state = DOOR_OPEN;
		door->open_timer = 1.5;
	}
	else
	{
		door->offset -= door->speed * delta_time;
		if (door->offset <= 0.0)
		{
			door->offset = 0.0;
			door->state = DOOR_CLOSED;
		}
	}
}

/**
 * @brief Manages the duration a door remains open before starting to close.
 *
 * If an entity (player or NPC) is currently standing on the door tile, the
 * open timer is refreshed to keep the door open.
 * Otherwise, the timer counts down based on the frame's delta time.
 * Once the timer expires, the door state is set to DOOR_CLOSING to initiate
 * the closing animation.
 *
 * @param game Pointer to the game state, used to check entity positions.
 * @param door Pointer to the currently open door being updated.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
static void	handle_open_door(t_game *game, t_door *door, double delta_time)
{
	if (is_entity_on_door(game, door))
		door->open_timer = 1.5;
	else
	{
		door->open_timer -= delta_time;
		if (door->open_timer <= 0.0)
			door->state = DOOR_CLOSING;
	}
}

/**
 * @brief Updates the state of all doors in the game world.
 *
 * This function iterates over all doors and updates their state based on the
 * player's distance and elapsed time. If the player is close enough to a
 * closed door, it begins opening. If the door is already opening, it is
 * progressively opened. Once fully open, the door remains open for a duration
 * and then starts closing unless an entity is standing on it.
 *
 * @param game Pointer to the game state containing doors and player info.
 * @param delta_time Time elapsed since the last frame (in seconds).
 */
void	update_doors(t_game *game, double delta_time)
{
	t_door	*door;
	int		i;
	double	distance;

	i = 0;
	while (i < game->door_count)
	{
		door = game->doors[i];
		distance = ft_euclidean_dist_dpoint(game->player.pos, door->pos);
		if (distance <= 2.0 && door->state == DOOR_CLOSED)
			door->state = DOOR_OPENING;
		if (door->state == DOOR_OPENING)
			open_door(door, delta_time);
		else if (door->state == DOOR_CLOSING)
			close_door(game, door, delta_time);
		else if (door->state == DOOR_OPEN)
			handle_open_door(game, door, delta_time);
		i++;
	}
}
