# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 18:23:28 by nlouis            #+#    #+#              #
#    Updated: 2025/02/20 20:28:11 by nlouis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I libft/include -I ./include -I mlx/ # -g -fsanitize=address -fsanitize=undefined

NAME = cub3d
NAME_BONUS = cub3d_bonus

SRCS =  mandatory/srcs/main.c \
		mandatory/srcs/init_game.c \
		mandatory/srcs/utils/utils.c \
		mandatory/srcs/utils/free_memory.c \
		mandatory/srcs/utils/x_memory_utils.c \
		mandatory/srcs/textures/load_textures.c \
		mandatory/srcs/rendering/render_scene.c \
		mandatory/srcs/rendering/caluclate_ray_properties.c \
		mandatory/srcs/rendering/utils.c \
		mandatory/srcs/parsing/parse_map.c \
		mandatory/srcs/parsing/extract_file_content.c \
		mandatory/srcs/parsing/parse_map_layout_helpers.c \
		mandatory/srcs/parsing/process_color_key.c \
		mandatory/srcs/parsing/process_config.c \
		mandatory/srcs/hooks/handle_hooks.c \
		mandatory/srcs/hooks/utils.c \
		mandatory/srcs/game/game_loop.c \
		mandatory/srcs/game/moves/move_player.c \
		mandatory/srcs/game/moves/rotate_camera.c

SRCS_BONUS =	bonus/srcs/main.c \
				bonus/srcs/init_game.c \
				bonus/srcs/utils/utils.c \
				bonus/srcs/utils/free_memory.c \
				bonus/srcs/utils/x_memory_utils.c \
				bonus/srcs/textures/load_textures.c \
				bonus/srcs/rendering/render_scene.c \
				bonus/srcs/rendering/caluclate_ray_properties.c \
				bonus/srcs/rendering/utils.c \
				bonus/srcs/parsing/parse_map.c \
				bonus/srcs/parsing/extract_file_content.c \
				bonus/srcs/parsing/parse_map_layout_helpers.c \
				bonus/srcs/parsing/process_color_key.c \
				bonus/srcs/parsing/process_config.c \
				bonus/srcs/hooks/handle_hooks.c \
				bonus/srcs/hooks/utils.c \
				bonus/srcs/game/game_loop.c \
				bonus/srcs/game/moves/move_player.c \
				bonus/srcs/game/moves/rotate_camera.c

OBJSDIR = objs
OBJSDIR_BONUS = objs
OBJS   = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJSDIR_BONUS)/,$(SRCS_BONUS:.c=.o))

LIBFT   = libft/lib/libft.a
LDFLAGS = -Llibft/lib -lft -Lmlx -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LDFLAGS)

$(LIBFT):
	make -C libft

$(OBJSDIR)/%.o: %.c include/cub3d.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR_BONUS)/%.o: %.c include/cub3d.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)  $(NAME_BONUS)
	rm -rf $(OBJSDIR) $(OBJSDIR_BONUS)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
