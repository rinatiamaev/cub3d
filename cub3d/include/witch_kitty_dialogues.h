/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   witch_kitty_dialogues.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riamaev <riamaev@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:20:27 by riamaev           #+#    #+#             */
/*   Updated: 2025/03/24 22:20:29 by riamaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WITCH_KITTY_DIALOGUES_H
# define WITCH_KITTY_DIALOGUES_H

# include "cub3d_bonus.h"

static char	*witch_kitty_dialogues[][11] = {
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
	"that fireball! It sounds dangerous!", NULL
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
{"...",
	"We are ready to leave this place?",
	"Oh my Ladferatu!",
	"What are we waiting for let's go!"
}, {NULL}, {NULL}, {NULL}
};

void	init_witch_kitty_dialogues(t_game *game, t_npc *npc);

#endif
