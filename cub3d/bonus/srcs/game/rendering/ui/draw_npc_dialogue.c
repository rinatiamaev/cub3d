/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc_dialogue.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:58:30 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 01:25:48 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*get_current_dialogue_line(t_npc *npc)
{
	if (npc->dialogue.current_line
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
		npc->dialogue.current_line = 0;
	return (npc->dialogue.dialogues
		[npc->dialogue.phase][npc->dialogue.current_line]);
}

void	render_npc_dialogue(t_game *game, t_npc *npc)
{
	int		x;
	int		y;
	int		color;
	char	*dialogue_text;

	x = ((WIN_W >> 1) - 128);
	y = (WIN_H - (WIN_H / 5));
	color = 43;
	dialogue_text = get_current_dialogue_line(npc);
	if (!dialogue_text)
		return ;
	mlx_put_image_to_window(game->mlx, game->window->ptr,
		game->tex.dialogue_box.ptr, x, y);
	mlx_string_put
		(game->mlx, game->window->ptr, x + 15, y + 35, color, dialogue_text);
}

static bool	should_draw_npc_dialogue(t_npc *npc)
{
	if (npc->state != SPEAK)
		return (false);
	if (npc->dialogue.phase < 0 || npc->dialogue.phase >= 10)
		return (false);
	if (!npc->dialogue.dialogues[npc->dialogue.phase])
		return (false);
	if (npc->dialogue.current_line < 0
		|| npc->dialogue.current_line
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
		npc->dialogue.current_line = 0;
	return (true);
}

void	draw_npc_dialogue(t_game *game)
{
	int		i;
	t_npc	*npc;

	i = 0;
	while (i < game->npc_count)
	{
		npc = game->npcs[i];
		if (should_draw_npc_dialogue(npc))
			render_npc_dialogue(game, npc);
		i++;
	}
}
