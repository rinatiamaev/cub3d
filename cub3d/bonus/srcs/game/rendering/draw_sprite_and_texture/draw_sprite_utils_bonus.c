/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:09:11 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 18:12:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Transforms the sprite's position into camera space.
 *
 * This function takes the sprite's relative position to the player and
 * transforms it into camera space using the player's direction and camera
 * plane vectors. It computes the determinant of the transformation matrix,
 * ensures it is valid (non-zero), and applies the inverse to get the final
 * `transform.x` (horizontal offset) and `transform.y` (depth).
 *
 * If the sprite ends up behind the player (transform.y ≤ 0), it is
 * considered not visible and the function returns false.
 *
 * @param data Pointer to the sprite draw data (contains relative position).
 * @param player The player structure with facing direction and view plane.
 * @return true if the sprite is in front of the player and can be rendered,
 *         false otherwise.
 */
static bool	compute_sprite_transform(t_sprite_draw *data, t_player player)
{
	t_dpoint	rel;
	double		det;
	double		inv_det;

	rel = data->relative_position;
	det = compute_determinant(player);
	if (fabs(det) < 0.000001)
		return (false);
	inv_det = compute_inverse_determinant(det);
	data->transform.x = compute_transform_x(player, rel, inv_det);
	data->transform.y = compute_transform_y(player, rel, inv_det);
	return (is_sprite_in_front(data->transform.y));
}

/**
 * @brief Computes the current animation frame index based on elapsed time.
 *
 * This function determines which frame of a sprite animation should be
 * displayed at the current moment. It calculates the time elapsed since the
 * animation started (`anim_start`), then divides by the duration of each
 * frame to determine the active frame index.
 *
 * The result is wrapped using modulo to loop the animation.
 *
 * Time is measured in microseconds using `gettimeofday()`.
 *
 * @param anim_start The animation start time in microseconds.
 * @param num_frames Total number of frames in the animation.
 * @param frame_duration_ms Duration of each frame in milliseconds.
 * @return The index of the current frame to display (0 to num_frames - 1).
 */
static int	get_current_frame(double anim_start, int num_frames,
												int frame_duration_ms)
{
	struct timeval	tv;
	long			current_time;
	long			elapsed_ms;
	int				frame_index;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000000L + tv.tv_usec;
	elapsed_ms = (current_time - anim_start) / 1000;
	frame_index = (elapsed_ms / frame_duration_ms) % num_frames;
	return (frame_index);
}

/**
 * @brief Selects the current animation frame for the sprite.
 *
 * This function determines which frame of the sprite's idle animation
 * should be displayed, based on how much time has passed since the
 * animation started. It uses a fixed frame duration of 200 milliseconds.
 *
 * The selected frame index is stored in `data->current_frame`, and the
 * corresponding texture pointer is assigned to `data->texture`.
 *
 * @param data Pointer to the sprite draw data (output: frame and texture).
 * @param sprite Pointer to the sprite containing animation state and frames.
 */
static void	select_sprite_frame(t_sprite_draw *data, t_sprite *sprite)
{
	data->current_frame = get_current_frame(sprite->anim_start,
			sprite->idle_frames_count, 200.0);
	data->texture = &sprite->idle_frames[data->current_frame];
}

/**
 * @brief Initializes the sprite draw data for rendering.
 *
 * This function prepares all necessary information to render a sprite by:
 *
 * 1. Computing the relative position from the player to the sprite.
 * 2. Transforming the sprite into camera space (to determine screen position).
 * 3. Calculating the on-screen bounding box for the sprite.
 * 4. Selecting the current animation frame texture.
 *
 * If the sprite is not visible (e.g. behind the player or off-screen),
 * the function returns false to skip rendering.
 *
 * @param data Pointer to the sprite draw structure to initialize.
 * @param player The player structure (position and orientation).
 * @param sprite The sprite to be rendered.
 * @return true if the sprite is visible and drawable, false otherwise.
 */
bool	init_sprite_draw_data(t_sprite_draw *data, t_player player,
															t_sprite *sprite)
{
	data->relative_position = get_direction_vector(player.pos, sprite->pos);
	if (!compute_sprite_transform(data, player))
		return (false);
	if (!calc_sprite_screen_coords(data))
		return (false);
	select_sprite_frame(data, sprite);
	return (true);
}
