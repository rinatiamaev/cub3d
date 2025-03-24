/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:19:50 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 14:19:05 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*   get_current_sprite_frame
*   Computes the current animation frame for the sprite based on elapsed
*   time. It uses gettimeofday() to measure how many milliseconds have
*   passed since the sprite animation started (sprite->anim_start) and then
*   calculates the frame index using the provided frame_duration_ms.
*/
int	get_current_frame(double anim_start, int num_frames,
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
