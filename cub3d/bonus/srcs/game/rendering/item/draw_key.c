/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:16:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/19 08:48:35 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_key(t_game *game, t_item *item, double *z_buffer)
{
	draw_sprite(game, game->player, &item->sprite, z_buffer);
}
