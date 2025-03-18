/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_npc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:09:21 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/17 20:47:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_npc	*find_closest_npc(t_game *game, double max_distance)
{
	t_npc	*closest_npc;
	double	closest_dist;
	double	current_dist;
	int		i;

	closest_npc = NULL;
	closest_dist = max_distance;
	i = 0;
	while (i < game->npc_count)
	{
		current_dist
			= ft_cab_dist_dpoint(game->player.pos, game->npcs[i]->pos);
		if (current_dist < closest_dist)
		{
			closest_dist = current_dist;
			closest_npc = game->npcs[i];
		}
		i++;
	}
	return (closest_npc);
}

bool	advance_npc_dialogue(t_npc *npc, t_story_state *story)
{
	if (npc->state != SPEAK)
		return (false);
	npc->dialogue.current_line++;
	if (npc->dialogue.current_line
		>= npc->dialogue.dialogue_count[npc->dialogue.phase])
	{
		if (ft_strcmp(npc->name, "witch kitty") == 0)
			story->has_spoken_to_witch = true;
		if (ft_strcmp(npc->name, "calico kitty") == 0)
			story->has_spoken_to_calico = true;
		if (ft_strcmp(npc->name, "fire spirit") == 0)
			story->has_spoken_to_fire_spirit = true;
		npc->dialogue.current_line = 0;
		npc->state = WAIT;
	}
	return (true);
}

void trigger_splash_animation(t_player *player)
{
	player->is_splashing = true;
	player->sprite.anim_index = 0;
	player->sprite.anim_timer = 0.0;
}

bool	handle_npc_chase(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 4.0);
	if (npc && npc->state == CHASE
		&& game->player.has_water
		&& has_line_of_sight(game, game->player.pos, npc->pos))
	{
		npc->is_hit = true;
		trigger_splash_animation(&game->player);
		return (false);
	}
	return (true);
}

static bool	handle_npc_speak(t_game *game)
{
	t_npc	*npc;

	npc = find_closest_npc(game, 2.0);
	if (!npc || npc->state == SPEAK)
		return (false);
	npc->state = SPEAK;
	return (true);
}

bool	interact_with_npc(t_game *game)
{
	if (!handle_npc_chase(game))
		return (false);
	return (handle_npc_speak(game));
}
