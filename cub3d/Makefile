# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 18:23:28 by nlouis            #+#    #+#              #
#    Updated: 2025/02/19 13:33:39 by nlouis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I libft/include -I ./include -I mlx/  -g -fsanitize=address -fsanitize=undefined

NAME = cub3d

SRCS =  srcs/main.c \
		srcs/init_game.c \
		srcs/render_scene.c \
		srcs/game_loop.c \
		srcs/handle_hooks.c \
		srcs/move_player.c \
		srcs/rotate_camera.c \
		srcs/utils/utils.c \
		srcs/utils/free_memory.c \
		srcs/utils/x_memory_utils.c \
		srcs/load_textures.c \
		srcs/parsing/parse_map.c

OBJSDIR = objs
OBJS   = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

LIBFT   = libft/lib/libft.a
LDFLAGS = -Llibft/lib -lft -Lmlx -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	make -C libft

$(OBJSDIR)/%.o: %.c include/cub3d.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJSDIR)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
