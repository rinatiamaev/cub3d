/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:01:12 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 14:44:28 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Advances the ray one step in the DDA algorithm.
 *
 * Compares the current side distances in the X and Y directions and steps
 * toward the next map square along the shortest direction. It updates the
 * side distance, the map coordinates, and sets the side flag to indicate
 * whether a vertical (0) or horizontal (1) wall was crossed.
 *
 * This function is used repeatedly in the DDA loop until a hit is detected.
 *
 * @param ray Pointer to the ray structure containing DDA state.
 */
static inline void	advance_dda_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step_dir.x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step_dir.y;
		ray->side = 1;
	}
}

/**
 * @brief Checks if the ray has hit a wall or gone out of map bounds.
 *
 * This function determines whether the ray's current grid cell corresponds
 * to a wall, or if the ray has stepped outside the map boundaries. If so,
 * it marks the ray as having hit an obstacle by setting `ray->hit` to 1.
 *
 * @param game Pointer to the game state (provides access to the map matrix).
 * @param ray Pointer to the ray containing the current map position.
 * @return true if a wall or out-of-bounds was hit, false otherwise.
 */
static inline bool	is_wall_hit(t_game *game, t_ray *ray)
{
	if (ray->map.x < 0 || ray->map.x >= game->map->size.x
		|| ray->map.y < 0 || ray->map.y >= game->map->size.y)
	{
		ray->hit = 1;
		return (true);
	}
	if (game->map->matrix[ray->map.y][ray->map.x] == WALL)
	{
		ray->hit = 1;
		return (true);
	}
	return (false);
}

/**
 * @brief Checks if the ray has hit a fully closed door.
 *
 * If the door exists and its opening offset is zero or less (fully closed),
 * the function marks the ray as having hit a closed door by setting
 * `ray->hit` to 2.
 *
 * @param ray Pointer to the ray being cast.
 * @param door Pointer to the door located at the ray's current map position.
 * @return true if the door is fully closed and blocks the ray,
 *         false otherwise.
 */
static inline bool	is_closed_door_hit(t_ray *ray, t_door *door)
{
	if (door && door->offset <= 0.0)
	{
		ray->hit = 2;
		return (true);
	}
	return (false);
}

/**
 * @brief Checks if the ray hits a partially open door.
 *
 * This function performs a precise check to determine whether the ray hits
 * the solid part of a door that is not fully open. It computes the exact
 * intersection point on the door plane based on the ray's side and compares
 * it with the current opening offset of the door.
 *
 * If the ray intersects a solid (non-opened) portion of the door, the hit is
 * registered by setting `ray->hit` to 2.
 *
 * @param game Pointer to the game state (provides player position).
 * @param ray Pointer to the ray being cast.
 * @param door Pointer to the door located at the ray's current grid position.
 * @return true if the ray hits a solid portion of a partially open door,
 *         false otherwise.
 */
static inline bool	is_partially_open_door_hit(t_game *game, t_ray *ray,
																t_door *door)
{
	double	door_x;

	if (!door || door->offset >= 1.0)
		return (false);
	if (ray->side == 0)
		door_x = game->player.pos.y + ((ray->map.x - game->player.pos.x
					+ (1 - ray->step_dir.x) / 2.0) / ray->dir.x) * ray->dir.y;
	else
		door_x = game->player.pos.x + ((ray->map.y - game->player.pos.y
					+ (1 - ray->step_dir.y) / 2.0) / ray->dir.y) * ray->dir.x;
	door_x -= floor(door_x);
	if (door_x < (1.0 - door->offset))
	{
		ray->hit = 2;
		return (true);
	}
	return (false);
}

/**
 * @brief Performs the DDA loop to detect wall or door collisions.
 *
 * This function iteratively advances the ray through the 2D map grid using
 * the Digital Differential Analyzer (DDA) algorithm. At each step, it checks
 * whether the ray has hit a wall or a door (closed or partially open).
 *
 * - If a wall is hit, the ray is marked as such (`ray->hit = 1`) and the
 *   loop breaks.
 * - If a door is encountered, the function retrieves the corresponding door
 *   object and checks whether it is fully closed or the ray intersects a
 *   solid portion of a partially open door. If so, `ray->hit = 2` and the
 *   loop breaks.
 *
 * The loop stops when a hit is registered, storing the result in the ray
 * structure for further rendering.
 *
 * @param game Pointer to the game state (includes map and door data).
 * @param ray Pointer to the ray being cast, modified in-place.
 */
void	perform_dda(t_game *game, t_ray *ray)
{
	t_door	*door;

	while (ray->hit == 0)
	{
		advance_dda_step(ray);
		if (is_wall_hit(game, ray))
			break ;
		if (game->map->matrix[ray->map.y][ray->map.x] == DOOR
			|| game->map->matrix[ray->map.y][ray->map.x] == EXIT_DOOR)
		{
			door = find_door_at(game, ray->map);
			if (is_closed_door_hit(ray, door)
				|| is_partially_open_door_hit(game, ray, door))
				break ;
		}
	}
}
