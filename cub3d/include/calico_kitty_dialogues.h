/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calico_kitty_dialogues.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riamaev <riamaev@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:13:30 by riamaev           #+#    #+#             */
/*   Updated: 2025/03/24 22:13:34 by riamaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALICO_KITTY_DIALOGUES_H
# define CALICO_KITTY_DIALOGUES_H

# include "cub3d_bonus.h"

static char	*calico_kitty_dialogues[][11] = {
{"What a maze...", NULL},
{"Oh, someone godferdumpin' help me!",
	"My sibling and I are trapped here...",
	"I tried to find a way out...",
	"but a giant fire ball is wandering around!",
	"I'm too scared to get back to my...",
	"sibling or continue my search for an exit.",
	"Could you get rid of it for me?",
	"That's so kind of you...",
	"Thank you! I'll wait here for you!", NULL
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
	"Thank you so much for your help!",
	"Could you escort me to my sibling ?", NULL
},
{"I should look for an exit, but you are so...",
	"fearless, that we'll just rely on you!", NULL
},
{"...",
	"You find a way out!?",
	"Let's get the heaven out of here!",
	NULL
}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}
};

void	init_calico_kitty_dialogues(t_game *game, t_npc *npc);

#endif
