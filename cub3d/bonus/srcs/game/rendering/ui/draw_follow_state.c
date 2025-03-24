/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_follow_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:51:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 19:55:15 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
