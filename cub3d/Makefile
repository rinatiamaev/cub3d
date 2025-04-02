# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 18:23:28 by nlouis            #+#    #+#              #
#    Updated: 2025/04/02 22:02:16 by nlouis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I libft/include -I ./include -I mlx/ # -g -fsanitize=address -fsanitize=undefined

NAME = cub3D
NAME_BONUS = cub3D_bonus

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

# SRCS_BONUS := $(shell find bonus/srcs -name "*.c")

SRCS_BONUS =	bonus/srcs/events/handle_events_bonus.c \
				bonus/srcs/events/npc_interaction/npc_chase_bonus.c \
				bonus/srcs/events/npc_interaction/follow_player_bonus.c \
				bonus/srcs/events/npc_interaction/interact_with_npc_bonus.c \
				bonus/srcs/events/npc_interaction/npc_dialogue_bonus.c \
				bonus/srcs/events/handle_interaction_bonus.c \
				bonus/srcs/events/handle_pause_bonus.c \
				bonus/srcs/events/interaction_utils_bonus.c \
				bonus/srcs/events/item_interaction/interact_with_item_bonus.c \
				bonus/srcs/events/handle_mouse_bonus.c \
				bonus/srcs/events/door_interaction/interact_with_door_bonus.c \
				bonus/srcs/game/story_telling/get_dial_phase_bonus.c \
				bonus/srcs/game/story_telling/track_story_advancement_bonus.c \
				bonus/srcs/game/story_telling/track_npc_strory_bonus.c \
				bonus/srcs/game/move_entity/player/is_player_move_valid_bonus.c \
				bonus/srcs/game/move_entity/player/is_map_position_valid_player_bonus.c \
				bonus/srcs/game/move_entity/player/rotate_player_bonus.c \
				bonus/srcs/game/move_entity/player/handle_player_move_bonus.c \
				bonus/srcs/game/move_entity/player/move_player_bonus.c \
				bonus/srcs/game/move_entity/a_star_pathfinding/a_star_setup_bonus_bonus.c \
				bonus/srcs/game/move_entity/a_star_pathfinding/a_star_memory_bonus.c \
				bonus/srcs/game/move_entity/a_star_pathfinding/a_star_utils_bonus_bonus.c \
				bonus/srcs/game/move_entity/a_star_pathfinding/a_star_path_bonus_bonus.c \
				bonus/srcs/game/move_entity/a_star_pathfinding/a_star_heap_utils_bonus_bonus.c \
				bonus/srcs/game/move_entity/npc/setup_waypoints_bonus_bonus.c \
				bonus/srcs/game/move_entity/npc/move_npc_bonus.c \
				bonus/srcs/game/move_entity/npc/is_position_valid_npc_bonus.c \
				bonus/srcs/game/move_entity/npc/move_npc_patrol_bonus.c \
				bonus/srcs/game/move_entity/npc/move_npc_follow_bonus.c \
				bonus/srcs/game/move_entity/move_utils_bonus.c \
				bonus/srcs/game/doors/spawn_door_bonus.c \
				bonus/srcs/game/doors/update_doors_bonus.c \
				bonus/srcs/game/doors/spawn_door_utils_bonus.c \
				bonus/srcs/game/doors/spawn_exit_door_bonus.c \
				bonus/srcs/game/game_loop_bonus.c \
				bonus/srcs/game/fps/fps_bonus.c \
				bonus/srcs/game/npc/update_all_npcs_bonus.c \
				bonus/srcs/game/npc/change_fire_spirit_behavior_bonus.c \
				bonus/srcs/game/npc/spawn_npc_utils_bonus.c \
				bonus/srcs/game/npc/play_npc_animation_bonus.c \
				bonus/srcs/game/npc/spawn_witch_kitty_bonus.c \
				bonus/srcs/game/npc/spawn_calico_kitty_bonus.c \
				bonus/srcs/game/npc/update_enemy_npc_bonus.c \
				bonus/srcs/game/npc/spawn_fire_spirit_bonus.c \
				bonus/srcs/game/npc/update_npc_bonus.c \
				bonus/srcs/game/rendering/ui/draw_follow_state_bonus.c \
				bonus/srcs/game/rendering/ui/draw_lose_message_bonus.c \
				bonus/srcs/game/rendering/ui/draw_npc_dialogue_bonus.c \
				bonus/srcs/game/rendering/ui/draw_pause_message_bonus.c \
				bonus/srcs/game/rendering/ui/minimap/draw_minimap_bonus.c \
				bonus/srcs/game/rendering/ui/minimap/draw_minimap_utils_bonus.c \
				bonus/srcs/game/rendering/ui/draw_win_message_bonus.c \
				bonus/srcs/game/rendering/ui/draw_temp_message_bonus.c \
				bonus/srcs/game/rendering/ui/draw_item_state_bonus.c \
				bonus/srcs/game/rendering/draw_entities_bonus.c \
				bonus/srcs/game/rendering/player/draw_splash_bonus.c \
				bonus/srcs/game/rendering/render_scene_bonus.c \
				bonus/srcs/game/rendering/raycasting/init_ray_data_bonus.c \
				bonus/srcs/game/rendering/raycasting/raycast_bonus.c \
				bonus/srcs/game/rendering/raycasting/caluclate_ray_properties_bonus.c \
				bonus/srcs/game/rendering/raycasting/perform_dda_bonus.c \
				bonus/srcs/game/rendering/raycasting/calculate_texture_mapping_bonus.c \
				bonus/srcs/game/rendering/item/draw_key_bonus.c \
				bonus/srcs/game/rendering/npc/draw_kitty_npc_utils_bonus.c \
				bonus/srcs/game/rendering/npc/draw_kitty_npc_bonus.c \
				bonus/srcs/game/rendering/npc/draw_fire_spirit_bonus.c \
				bonus/srcs/game/rendering/draw_sprite_and_texture/compute_sprite_transform_utils_bonus.c \
				bonus/srcs/game/rendering/draw_sprite_and_texture/draw_texture_bonus.c \
				bonus/srcs/game/rendering/draw_sprite_and_texture/draw_sprite_column_bonus.c \
				bonus/srcs/game/rendering/draw_sprite_and_texture/draw_sprite_utils_bonus.c \
				bonus/srcs/game/rendering/draw_sprite_and_texture/calc_sprite_screen_coords_bonus.c \
				bonus/srcs/game/rendering/draw_sprite_and_texture/draw_sprite_bonus.c \
				bonus/srcs/game/rendering/fill_background_bonus.c \
				bonus/srcs/game/items/spawn_item_utils_bonus.c \
				bonus/srcs/game/items/spawn_well_bonus.c \
				bonus/srcs/game/items/spawn_bucket_bonus.c \
				bonus/srcs/game/items/spawn_key_bonus.c \
				bonus/srcs/game/items/spawn_tree_bonus.c \
				bonus/srcs/game/items/update_items_bonus.c \
				bonus/srcs/game/init_game/init_player_bonus.c \
				bonus/srcs/game/init_game/init_game_bonus.c \
				bonus/srcs/game/utils/has_line_of_sight_bonus.c \
				bonus/srcs/game/utils/game_utils_bonus.c \
				bonus/srcs/game/utils/load_textures_bonus.c \
				bonus/srcs/game/utils/check_win_condition_bonus.c \
				bonus/srcs/game/utils/sort_entities_bonus.c \
				bonus/srcs/main_bonus.c \
				bonus/srcs/parsing/convert_map_char_to_value_bonus.c \
				bonus/srcs/parsing/process_config_bonus.c \
				bonus/srcs/parsing/extract_file_content_bonus.c \
				bonus/srcs/parsing/parse_map_bonus.c \
				bonus/srcs/parsing/process_color_key_bonus.c \
				bonus/srcs/parsing/parse_map_layout_helpers_bonus.c \
				bonus/srcs/utils/x_memory_utils_two_bonus.c \
				bonus/srcs/utils/error_bonus.c \
				bonus/srcs/utils/x_memory_utils_one_bonus.c \
				bonus/srcs/utils/free_memory/free_memory_bonus.c \
				bonus/srcs/utils/free_memory/free_npcs_utils_bonus.c \
				bonus/srcs/utils/free_memory/free_npcs_bonus.c \
				bonus/srcs/utils/free_memory/free_items_bonus.c 

OBJSDIR = mandatory/objs
OBJSDIR_BONUS = bonus/objs
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
