/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:13:03 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/18 09:24:41 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_interaction(t_game *game)
{
	if (continue_npc_dialogue(game))
		return ;
	if (!handle_npc_chase(game))
		return ;
	if (!interact_with_door(game))
		interact_with_npc(game);
}
