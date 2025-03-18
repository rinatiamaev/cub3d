/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_witch_kitty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:23:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/17 20:08:26 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_witch_kitty_dialogues(t_game *game, t_npc *npc)
{
	static char	*dialogues[][11] = {
	{"At least we have a well nearby to drink from...", NULL },
	{"Hi! Finally awake!",
		"My sibling and I are trapped in this Labyrinth!",
		"He left to find an exit but never came back!",
		"He told me to wait here...",
		"could you look for him past this door?",
		"Please, I'm worried about him...",
		"thank you! I'll wait here for you!", NULL
	},
	{"...",
		"What a giant fireball is wandering around!?",
		"Oh my godferatu! I hope Calico is alright...",
		"will you still help me find him?",
		"Thank you, you're so brave!", NULL
	},
	{"...",
		"You found him! I am relieved...",
		"bring him back please!", NULL
	},
	{"...",
		"You found him! I am relieved but scared...",
		"at the same time, I hope you can get rid of...",
		"ahat fireball! It sounds dangerous!", NULL
	},
	{"...",
		"The fireball was an angry spirit!?",
		"Good thing you cooled it down!",
		"Hopefully, it won't get mad again...",
		"Could you still bring Calico back to me?", NULL
	},
	{"...",
		"Thank you so much for bringing him back!",
		"We just have to find a way out now...", NULL
	},
	{"You found a key ?! We just need a door now!", NULL },
	{"You found a locked door ?! We just need a key now!", NULL },
	{"We are ready to leave this place, oh my godferatu!",
		"What are we waiting for let's go!"
	}, {NULL}
	};

	npc->dialogue.phase_count = sizeof(dialogues) / sizeof(dialogues[0]);
	allocate_dialogues
		(game, &npc->dialogue, dialogues, npc->dialogue.phase_count);
}

static void	init_witch_kitty_sprites(t_npc *npc)
{
	static char	*idle_frames[] = {
		WS0, WS1, WS2, WS3, WS4, WS5, WS6, WS7, WS8, WS9, WS10, WS11, WS12, WS13
	};
	static char	*move_frames[] = {
		WK_WAWAY0, WK_WAWAY1, WK_WAWAY2, WK_WAWAY3,
		WK_WTOW0, WK_WTOW1, WK_WTOW2, WK_WTOW3,
		WK_WLEFT0, WK_WLEFT1, WK_WLEFT2, WK_WLEFT3,
		WK_WRI0, WK_WRI1, WK_WRI2, WK_WRI3
	};
	static char	*speak_frames[] = {
		WK_C0, WK_C1, WK_C2, WK_C3, WK_C4, WK_C5,
		WK_C6, WK_C7, WK_C8, WK_C9, WK_C10, WK_C11
	};

	npc->sprite.size = (t_point){64, 64};
	npc->sprite.idle_paths = idle_frames;
	npc->sprite.idle_frames_count
		= sizeof(idle_frames) / sizeof(idle_frames[0]);
	npc->sprite.move_paths = move_frames;
	npc->sprite.move_frames_count
		= sizeof(move_frames) / sizeof(move_frames[0]);
	npc->sprite.speak_paths = speak_frames;
	npc->sprite.speak_frames_count
		= sizeof(speak_frames) / sizeof(speak_frames[0]);
}

static void	init_witch_kitty(t_game *game, t_npc *npc, t_dpoint pos)
{
	npc->type = "kitty";
	npc->name = "witch kitty";
	npc->pos.x = pos.x + 0.5;
	npc->pos.y = pos.y + 0.5;
	npc->speed = 1.2;
	init_npc_pathfinding(game, npc);
	generate_npc_waypoints(npc, game);
	init_witch_kitty_sprites(npc);
	init_sprite_frames_and_animation_npc(game, &npc->sprite);
	init_witch_kitty_dialogues(game, npc);
}

void	spawn_witch_kitty(t_game *game, double x, double y)
{
	t_npc		*npc;
	t_dpoint	pos;

	npc = x_calloc(game, 1, sizeof(t_npc));
	pos = (t_dpoint){x, y};
	init_witch_kitty(game, npc, pos);
	update_npc_list(game, npc);
}
