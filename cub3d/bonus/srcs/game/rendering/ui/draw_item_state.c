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

static void	get_bucket_mess(t_player *player, char *message, size_t size)
{
	if (player->has_water)
		ft_strlcpy(message, "You have a bucket filled with water!", size);
	else if (player->has_bucket)
		ft_strlcpy(message, "You have an empty bucket!", size);
	else
		message[0] = '\0';
}

static void	get_key_message(t_player *player, char *message, size_t size)
{
	if (player->has_key)
		ft_strlcpy(message, "You have a key!", size);
	else
		message[0] = '\0';
}

void	draw_bucket_state(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char	bucket_mess[50];
	char	key_message[50];

	get_bucket_mess(&game->player, bucket_mess, sizeof(bucket_mess));
	get_key_message(&game->player, key_message, sizeof(key_message));
	x = (WIN_W - 260);
	y = 70;
	color = 43;
	if (bucket_mess[0] || key_message[0])
		mlx_put_image_to_window
			(game->mlx, game->window->ptr, game->tex.dialogue_box.ptr, x, y);
	if (bucket_mess[0])
		mlx_string_put
			(game->mlx, game->window->ptr, x + 15, y + 25, color, bucket_mess);
	if (key_message[0])
		mlx_string_put
			(game->mlx, game->window->ptr, x + 15, y + 45, color, key_message);
}
