/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_calico_kitty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:05:57 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/13 16:10:10 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_calico_kitty_dialogues(t_game *game, t_npc *npc)
{
	static char	*dialogues[][11] = {
	{"What a maze...", NULL},
	{"Oh, someone godferdumpin' help me!",
		"I'm shlooby stuck here, a giant fire ball...",
		"is wandering in there! I found a kind of...",
		"watergun, but it's empty! I would need to go...",
		"to the well to fill it up, but I'm too scared...",
		"to go there while this fireball is around...",
		"Could you fill up the watergun and get rid of...",
		"the fireball for me?",
		"Thank you! I'll wait here for you!", NULL
	},
	{"...",
		"You got rid of that fireball!?",
		"Thank you so much!",
		"I can't believe it is a spirit...",
		"I hope it won't get mad again...",
		"Well done! Would you like to help me get back to...",
		"my sibling? I'm sure he's worried about me...", NULL
	},
	{"...",
		"You saw the fireball!?",
		"I hope you can get rid of it...", NULL
	},
	{"...",
		"The fireball was an angry spirit!?",
		"Good thing you cooled it down!",
		"Hopefully, it won't get mad again...",
		"Could you escort me to my sibling ?", NULL
	},
	{"...",
		"You got rid of the fireball!?",
		"It turned into a nice blue fireball ?!",
		"Weeeeiiiirrrd! But cool!",
		"Hopefully, it won't get mad again...",
		"Thank you so much for your help!",
		"Could you escort me to my sibling ?", NULL
	},
	{"I should look for an exit, but you are so...",
		"fearless, that we'll just rely on you!", NULL},
	{"A key, nice!", NULL },
	{"A locked door, nice!", NULL },
	{"Let's get the hell out of here!", NULL}, {NULL}
	};

	npc->dialogue.phase_count = sizeof(dialogues) / sizeof(dialogues[0]);
	allocate_dialogues
		(game, &npc->dialogue, dialogues, npc->dialogue.phase_count);
}

static void	init_calico_kitty_sprites(t_npc *npc)
{
	static char	*idle_frames[] = {
		CK0, CK1, CK2, CK3, CK4, CK5, CK6, CK7, CK8, CK9, CK10, CK11, CK12
	};
	static char	*move_frames[] = {
		CK_WTOW0, CK_WTOW1, CK_WTOW2, CK_WTOW3,
		CK_WAWAY0, CK_WAWAY1, CK_WAWAY2, CK_WAWAY3,
		CK_WLEFT0, CK_WLEFT1, CK_WLEFT2, CK_WLEFT3,
		CK_WRI0, CK_WRI1, CK_WRI2, CK_WRI3
	};
	static char	*speak_frames[] = {
		CK_C0, CK_C1, CK_C2, CK_C3, CK_C4, CK_C5, CK_C6, CK_C7, CK_C8, CK_C9
	};

	npc->sprite.size = (t_point){64, 64};
	npc->sprite.idle_paths = idle_frames;
	npc->sprite.num_idle_frames
		= sizeof(idle_frames) / sizeof(idle_frames[0]);
	npc->sprite.move_paths = move_frames;
	npc->sprite.move_frames_count
		= sizeof(move_frames) / sizeof(move_frames[0]);
	npc->sprite.speak_paths = speak_frames;
	npc->sprite.speak_frames_count
		= sizeof(speak_frames) / sizeof(speak_frames[0]);
}

static void	init_calico_kitty(t_game *game, t_npc *npc, t_dpoint pos)
{
	npc->type = "kitty";
	npc->name = "calico kitty";
	npc->is_hit = false;
	npc->pos.x = pos.x + 0.5;
	npc->pos.y = pos.y + 0.5;
	npc->speed = 0.2;
	npc->patrol_range = 10;
	npc->waypoint_count = 4;
	npc->current_wp = 1;
	npc->threshold_dist = 0.2;
	npc->astar = x_calloc(game, 1, sizeof(t_astar));
	npc->astar->direction[0] = (t_point){0, -1};
	npc->astar->direction[1] = (t_point){0, 1};
	npc->astar->direction[2] = (t_point){-1, 0};
	npc->astar->direction[3] = (t_point){1, 0};
	generate_npc_waypoints(npc, game);
	init_calico_kitty_sprites(npc);
	init_sprite_frames_and_animation(game, &npc->sprite);
	init_calico_kitty_dialogues(game, npc);
}

void	spawn_calico_kitty(t_game *game, double x, double y)
{
	t_npc		*npc;
	t_dpoint	pos;

	npc = x_calloc(game, 1, sizeof(t_npc));
	pos = (t_dpoint){x, y};
	init_calico_kitty(game, npc, pos);
	update_npc_list(game, npc);
}
