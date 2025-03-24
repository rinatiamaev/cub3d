/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:33:37 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:36:44 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_fps(t_game *game, double delta_time)
{
	game->frame_count++;
	game->fps_time_acc += delta_time;
	if (game->fps_time_acc >= 1.0)
	{
		game->fps = game->frame_count / game->fps_time_acc;
		game->frame_count = 0;
		game->fps_time_acc = 0.0;
	}
}

static void	draw_fps(t_game *game)
{
	char	*fps_str;
	char	*prefix;
	char	*msg;

	fps_str = x_itoa(game, game->fps);
	prefix = x_strdup(game, "FPS: ");
	msg = x_strjoin_free(game, prefix, fps_str);
	mlx_string_put
		(game->mlx, game->window->ptr, WIN_W - 60, WIN_H - 40, 0xFFFFFF, msg);
	free(msg);
}

int	game_loop(t_game *game)
{
	double	delta_time;

	if (!handle_game_state(game))
		return (0);
	delta_time = get_delta_time();
	update_fps(game, delta_time);
	handle_player_moves(game, delta_time);
	handle_mouse_movement(game, game->window);
	update_entities_sort(game);
	update_all_npcs(game, delta_time);
	update_items(game, delta_time);
	update_doors(game, delta_time);
	update_story(game);
	update_temp_message(game, delta_time);
	check_win_condition(game);
	render_scene(game, delta_time);
	draw_fps(game);
	return (0);
}
