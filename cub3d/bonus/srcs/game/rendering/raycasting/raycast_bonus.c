/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:05:56 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 14:40:44 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Selects the appropriate texture for the current wall hit.
 *
 * This function determines which wall texture should be used based on the
 * side of the wall that was hit and the ray's direction. It handles both
 * standard wall sides and doors:
 *
 * - If the ray hit a door (`ray->hit == 2`), it checks whether the door is
 *   a normal or exit door and returns the corresponding texture.
 * - If the ray hit a vertical wall (side == 0), the direction of the ray in
 *   the X axis determines whether it's an east or west wall.
 * - If the ray hit a horizontal wall (side == 1), the Y direction determines
 *   whether it's a north or south wall.
 *
 * @param game Pointer to the game state (access to textures and doors).
 * @param ray Pointer to the ray that hit the wall.
 * @return Pointer to the selected wall or door texture.
 */
static inline t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	t_door	*door;

	if (ray->hit == 2)
	{
		door = find_door_at(game, ray->map);
		if (door && door->type == EXIT_DOOR_TYPE)
			return (&game->tex.exit_door);
		return (&game->tex.door);
	}
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (&game->tex.ea);
		else
			return (&game->tex.we);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->tex.so);
		else
			return (&game->tex.no);
	}
}

/**
 * @brief Retrieves the color of a texture pixel without alpha processing.
 *
 * This function accesses the texture buffer to retrieve the raw color value
 * at coordinates (x, y). It assumes 32-bit color and does not perform any
 * transparency or alpha channel handling — the pixel is returned as-is.
 *
 * It uses the texture's line size and bits-per-pixel (bpp) to correctly
 * compute the memory offset to the desired pixel.
 *
 * @param tex Pointer to the texture structure.
 * @param x X coordinate in the texture.
 * @param y Y coordinate in the texture.
 * @return The color value of the specified pixel.
 */
static inline int	get_tex_color_no_alpha(t_texture *tex, int x, int y)
{
	unsigned int	*pixel_ptr;
	unsigned int	color;

	pixel_ptr
		= (unsigned int *)(tex->addr + y
			* tex->line_size + x * (tex->bpp >> 3));
	color = *pixel_ptr;
	return (color);
}

/**
 * @brief Draws a vertical column of a wall texture to the screen.
 *
 * This function renders a single vertical stripe of a wall on the screen,
 * corresponding to one raycast column (`*x`). It performs the following steps:
 *
 * 1. Selects the appropriate wall or door texture based on ray hit data.
 * 2. Calculates the starting position in the image buffer where the column
 *    should be drawn.
 * 3. Iterates over each pixel in the vertical range from `draw_start` to
 *    `draw_end`, sampling the corresponding Y coordinate from the texture.
 * 4. Retrieves the texture color at `(tex.x, tex.y)` with no alpha handling.
 * 5. Writes the color to the screen buffer.
 *
 * Texture Y coordinates are incremented using `ray->step` to ensure proper
 * vertical scaling, and wrapping is handled using a bitwise AND with texture
 * height (assuming a power-of-two height).
 *
 * @param game Pointer to the game state, including the rendering buffer.
 * @param ray Pointer to the ray with rendering properties and texture mapping.
 * @param x Pointer to the current screen column being rendered.
 */
void	draw_wall_column(t_game *game, t_ray *ray, int *x)
{
	t_texture	*tex;
	int			y;
	char		*dst;
	int			color;

	tex = select_wall_texture(game, ray);
	y = ray->draw_start;
	dst = game->img.addr + (y * game->img.line_size)
		+ ((*x) * (game->img.bpp >> 3));
	while (y <= ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (tex->size.y - 1);
		ray->tex_pos += ray->step;
		color = get_tex_color_no_alpha(tex, ray->tex.x, ray->tex.y);
		*(unsigned int *)dst = color;
		dst += game->img.line_size;
		y++;
	}
}

/**
 * @brief Casts a single ray and renders the corresponding vertical wall slice.
 *
 * This function performs the full raycasting pipeline for one vertical column
 * on the screen. It includes:
 *
 * 1. **Ray initialization** (`init_ray`): Computes direction and grid position
 *    based on the player's view and the current screen column.
 * 2. **DDA setup** (`init_dda_ray`): Calculates stepping directions and
 *    initial distances to grid lines.
 * 3. **DDA loop** (`perform_dda`): Advances through the map grid until hitting
 *    a wall or door, using the DDA algorithm.
 * 4. **Property calculation** (`calculate_ray_properties`): Computes wall
 *    height, screen bounds, and texture mapping data.
 * 5. **Rendering** (`draw_wall_column`): Draws the vertical slice for the ray.
 * 6. **Z-buffer update**: Stores the perpendicular wall distance for use in
 *    later sprite rendering or depth testing.
 *
 * @param game Pointer to the game state.
 * @param ray Pointer to the ray structure used during casting.
 * @param x Pointer to the current screen column index (auto increments).
 * @param z_buffer Array storing the wall distance for each column.
 */
void	raycast(t_game *game, t_ray *ray, int *x, double *z_buffer)
{
	init_ray(game, ray, *x);
	init_dda_ray(game, ray);
	perform_dda(game, ray);
	calculate_ray_properties(game, ray);
	draw_wall_column(game, ray, x);
	z_buffer[(*x)++] = ray->perp_w_dist;
}
