/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bucket_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:18:38 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 13:51:26 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	get_bucket_message(t_player *player, char *message, size_t size)
{
	if (player->has_bucket)
	{
		if (player->has_water)
			ft_strlcpy(message, "You have a bucket filled with water!", size);
		else
			ft_strlcpy(message, "You have an empty bucket!", size);
	}
}

void	draw_bucket_state(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char    bucket_message[50];

	if (!game->player.has_bucket)
		return ;
	get_bucket_message(&game->player, bucket_message, sizeof(bucket_message));
	x = (WIN_W - 260);
	y = 70;
	color = 43;
	mlx_put_image_to_window
		(game->mlx, game->window->ptr, game->tex.dialogue_box.ptr, x, y);
	mlx_string_put
		(game->mlx, game->window->ptr, x + 15, y + 35, color, bucket_message);
}
