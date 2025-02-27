/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:05:31 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/27 21:41:49 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	sort_sprites(t_game *game, t_player player, t_sprite **sprites)
{
	int		i;
	int		j;
	double	dist_i;
	double	dist_j;

	i = 0;
	while (i < game->sprite_count - 1)
	{
		j = 0;
		while (j < game->sprite_count - i - 1)
		{
			dist_i = (sprites[j]->pos.x - player.pos.x)
				* (sprites[j]->pos.x - player.pos.x)
				+ (sprites[j]->pos.y - player.pos.y)
				* (sprites[j]->pos.y - player.pos.y);
			dist_j = (sprites[j + 1]->pos.x - player.pos.x)
				* (sprites[j + 1]->pos.x - player.pos.x)
				+ (sprites[j + 1]->pos.y - player.pos.y)
				* (sprites[j + 1]->pos.y - player.pos.y);
			if (dist_i < dist_j)
				ft_swap(&sprites[j], &sprites[j + 1], sizeof(t_sprite *));
			j++;
		}
		i++;
	}
}

static void	draw_sprite_column(t_game *game, t_sprite_draw *data)
{
	data->y = data->draw_start.y;
	while (data->y < data->draw_end.y)
	{
		data->d = (data->y * 256) - (WIN_H * 128) + (data->height * 128);
		data->texture_y
			= (int)((data->d * data->texture_size.y) / data->height) / 256;
		data->color = get_tex_color(data->texture, data->texture_x,
				data->texture_y);
		if (data->color != 42)
			put_pixel(&game->img, data->stripe_x, data->y, data->color);
		data->y++;
	}
}

static void	draw_sprite_stripe(t_game *game, t_sprite_draw *data,
														double *z_buffer)
{
	data->texture_x = (int)((256 * (data->stripe_x
					- (-data->width / 2 + data->screen_x))
				* data->texture_size.x / data->width) / 256
			);
	if (data->transform_y > 0
		&& data->stripe_x >= 0
		&& data->stripe_x < WIN_W
		&& data->transform_y < z_buffer[data->stripe_x])
		draw_sprite_column(game, data);
}

void	draw_sprite(t_game *game, t_player player, t_sprite *sprite,
														double *z_buffer)
{
	t_sprite_draw	data;

	if (!init_sprite_draw_data(&data, player, sprite))
		return ;
	data.stripe_x = data.draw_start.x;
	while (data.stripe_x < data.draw_end.x)
	{
		draw_sprite_stripe(game, &data, z_buffer);
		data.stripe_x++;
	}
}

void	draw_sprites(t_game *game, t_player player, double *z_buffer)
{
	int	i;

	sort_sprites(game, player, game->sprites);
	i = 0;
	while (i < game->sprite_count)
	{
		if (ft_strcmp(game->sprites[i]->type, "witch_kitty") == 0)
			draw_witch_kitty(game, game->sprites[i], z_buffer);
		else
			draw_sprite(game, player, game->sprites[i], z_buffer);
		i++;
	}
}
