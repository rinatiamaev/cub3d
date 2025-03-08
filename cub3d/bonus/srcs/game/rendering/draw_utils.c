/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:19:50 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/08 00:05:49 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + ((y * img->line_size) + (x * (img->bpp / 8)));
	*(unsigned int *)dst = color;
}

int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= tex->size.x || y < 0 || y >= tex->size.y)
		return (42);
	pixel = tex->addr + (y * tex->line_size + x * (tex->bpp / 8));
	color = *(unsigned int *)pixel;
	if ((color & 0x00FFFFFF) == 0x000000)
		return (42);
	return (color);
}

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
