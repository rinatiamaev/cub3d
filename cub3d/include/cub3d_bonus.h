/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:08:40 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:53:05 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include "assets_path.h"

# include <mlx.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <stdint.h>
# include <string.h>

# define MINIMAP_SIZE		250
# define MINIMAP_OFFSET_X	20
# define MINIMAP_OFFSET_Y	20
# define PLAYER_SCALE		0.6
# define WALL_COLOR			0xFFFFFF
# define PLAYER_COLOR		0xFFFF00

# define SUCCESS	0
# define FAILURE	1

# define KEYPRESS			2
# define KEYRELEASE			3
# define FOCUS_IN			9
# define FOCUS_OUT			10
# define MINIMIZED			12
# define DESTROY_NOTIFY		17
# define CONFIGURE_NOTIFY	22

# define KEYPRESS_MASK			1
# define KEYRELEASE_MASK		2
# define FOCUS_CHANGE_MASK		2097152
# define STRUCTURE_NOTIFY_MASK	131072

# define FOV				0.66
// fov_threshold = cos(FOV / 2.0);
# define FOV_THRESHOLD		0.943956
# define INFINITY_DIST		1e6

# define UP				122
# define DOWN			115
# define LEFT			113
# define RIGHT			100
/* # define UP				119
# define DOWN			115
# define LEFT			100
# define RIGHT			97 */
# define ARR_RIGHT		65361
# define ARR_LEFT		65363
# define PAUSE			32
# define ESC			65307
# define TOGGLE_MINIMAP	109
# define INTERACTION	101
# define FOLLOW_PLAYER	102

# define WIN_NAME	"Cube3D"
# define WIN_W		1200
# define WIN_H		900

# define TEX_W		128
# define TEX_H		128

# define DEAD_ZONE	1.0

# define MAX_LINE_LENGTH	40
# define MAX_LINES			4

typedef enum e_char_value
{
	FREE_SPACE,
	WALL,
	CONF_DIR,
	EMPTY,
	WELL,
	BUCKET,
	DOOR,
	EXIT_DOOR
}	t_char_value;

typedef struct s_node
{
	t_point			pos;
	int				g_cost;
	int				h_cost;
	int				f_cost;
	struct s_node	*parent;
	struct s_node	*next;
}	t_node;

typedef struct s_closed_list
{
	t_node	**nodes;
	int		capacity;
	int		size;
}	t_closed_list;

typedef struct s_astar
{
	t_point				goal;
	t_closed_list		*closed_list;
	int					**open_list;
	t_node				*node;
	t_node				*current_node;
	t_point				direction[4];
}	t_astar;

typedef struct s_mouse_data
{
	t_point	position;
	t_point	center;
	double	delta_x;
	double	rotation_speed;
	double	sensitivity;
}	t_mouse_data;

typedef struct s_conf
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_color;
	int		ceiling_color;
}	t_conf;

typedef struct s_map
{
	int		fd;
	char	*filename;
	char	**file_content;
	t_conf	conf;
	char	**map_layout;
	t_point	size;
	int		player_count;
	int		**matrix;
}	t_map;

typedef struct s_window
{
	void	*ptr;
	char	*name;
	t_point	size;
	t_point	offset;
}	t_window;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_dpoint	dir;			// Ray direction
	t_point		map;			// Map square coordinates
	t_dpoint	delta_dist;		// Distance to next side in x and y
	t_dpoint	side_dist;		// Initial distance to next x or y side
	t_point		step_dir;		// Step direction in x and y (+1 or -1)
	int			hit;			// 1 if a wall was hit
	int			side;			// 0 for vertical side, 1 for horizontal side
	double		perp_w_dist;	// Perpendicular distance from player to wall
	int			line_height;	// Height of wall line to draw
	int			draw_start;		// Starting pixel for wall line
	int			draw_end;		// Ending pixel for wall line
	double		wall_x;			// Exact wall hit position
	t_point		tex;			// Texture coordinates 
	double		step;			// How much to increase texture coordinate
	double		tex_pos;		// Initial texture coordinate position
}	t_ray;

typedef struct s_texture
{
	void	*ptr;
	char	*addr;
	t_point	size;
	int		bpp;
	int		line_size;
	int		endian;
}	t_texture;

typedef struct s_sprite_draw
{
	t_dpoint	relative_position;		// Sprite position relative to player
	double		inverse_determinant;	// Inverse of the det of the camera mat
	t_dpoint	transform;				// Sprite position in camera space
	int			screen_x;				// X coordinate of sprite center screen
	int			height;					// Calculated sprite height on screen
	int			width;					// Calculated sprite width on screen
	t_point		draw_start;				// (top-left) of sprite bounding box
	t_point		draw_end;				// (bott-right) of sprite bounding box
	int			current_frame;			// Chosen animation frame
	t_texture	*texture;				// Pointer to the sprite texture
	int			stripe_x;				// Current vert stripe in screen space
	t_point		tex_pixel;				// Current pixel in texture
	int			color;					// Final color from texture
}	t_sprite_draw;

typedef enum e_npc_state
{
	WAIT,
	PATROL,
	FOLLOW,
	SPEAK,
	CHASE,
	HIT,
	BLOCKED
}	t_npc_state;

typedef enum e_walk_block
{
	WALK_AWAY,
	WALK_TOWARD,
	WALK_LEFT,
	WALK_RIGHT
}	t_walk_block;

typedef struct s_sprite
{
	t_dpoint	pos;
	t_point		size;
	char		**idle_paths;
	t_texture	*idle_frames;
	int			idle_frames_count;
	char		**move_paths;
	t_texture	*move_frames;
	int			move_frames_count;
	char		**speak_paths;
	t_texture	*speak_frames;
	int			speak_frames_count;
	char		**hit_paths;
	t_texture	*hit_frames;
	int			hit_frames_count;
	char		**splash_paths;
	t_texture	*splash_frames;
	int			splash_frames_count;
	t_texture	texture;
	int			anim_start;
	int			anim_index;
	double		anim_timer;
}	t_sprite;

typedef struct s_los
{
	t_point		map_check;
	t_point		step;
	t_dpoint	ray_dir;
	t_dpoint	side_dist;
	t_dpoint	delta_dist;
}	t_los;

typedef enum e_dial_phase
{
	IDLE,
	PHASE_0,
	PHASE_1,
	PHASE_2,
	PHASE_3,
	PHASE_4,
	PHASE_5,
	PHASE_6,
	PHASE_7,
	PHASE_8
}	t_dial_phase;

# define NOT_STARTED	0
# define SEARCHING		1
# define FOUND			2
# define LOCATED		3
# define WAITING		4
# define HELPED			5
# define SAVED			6
# define EXIT_SEARCH	7
# define UNLOCKED		8

typedef struct s_story_state
{
	bool	has_spoken_to_witch;
	bool	has_spoken_to_calico;
	bool	has_spoken_to_fire_spirit;
	int		sibling;
	int		fireball;
	int		key;
	int		exit;
} t_story_state;

typedef struct s_dial
{
	char			***dialogues;
	int				*dialogue_count;
	int				current_line;
	int 			phase_count;
	t_dial_phase	phase;
}	t_dial;

typedef struct s_npc
{
	char		*type;
	char		*name;
	t_dpoint	pos;
	t_npc_state	state;
	double		speed;
	double		following_speed;
	t_dpoint	move_vec;
	t_dpoint	last_move_vec;
	t_sprite	sprite;
	t_astar		*astar;
	t_dial		dialogue;
	int			patrol_range;
	t_dpoint	*waypoints;
	int			waypoint_count;
	int			current_wp;
	t_dpoint	*path;
	int			path_length;
	int			path_index;
	double		threshold_dist;
	bool		can_follow;
	bool		is_following;
	bool		is_enemy;
	bool		is_hit;
	double		hit_timer;
	double		hit_duration;
	bool		is_saved;
}	t_npc;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING,
	DOOR_LOCKED
}	t_door_state;

typedef enum e_door_type
{
	NORMAL_DOOR,
	EXIT_DOOR_TYPE
}	t_door_type;

typedef struct s_door
{
	t_door_type		type;
	t_dpoint		pos;
	double			offset;
	t_door_state	state;
	double			speed;
	double			open_timer;
}	t_door;

typedef struct s_item
{
	char		*type;
	char		*name;
	t_dpoint	pos;
	t_texture	texture;
	t_sprite	sprite;
	bool		is_collectible;
	bool		is_collected;
}	t_item;

typedef enum e_entity_type
{
	NPC,
	ITEM
}	t_entity_type;

typedef struct s_entity
{
	t_entity_type	type;
	t_dpoint		pos;
	void			*ptr;
}	t_entity;

typedef struct s_tex
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	t_texture	door;
	t_texture	exit_door;
	t_texture	dialogue_box;
}	t_tex;

typedef enum e_game_state
{
	RUNNING,
	PAUSED,
	GAME_OVER,
	WIN
}	t_game_state;

typedef struct s_player
{
	char		conf_dir;
	t_dpoint	pos;
	t_dpoint	last_pos;
	t_dpoint	facing_dir;		// Direction vector
	t_dpoint	view_plane;		// Camera plane vector: perp to facing_dir
	double		rot_speed;		// (in radians)
	double		move_speed;
	double		facing_angle; 	// (in radians)
	bool 		has_bucket;
	bool		has_water;
	bool		is_splashing;
	bool		has_key;
	t_sprite	sprite;
}	t_player;

typedef struct s_game
{
	t_game_state	state;
	t_story_state	story;
	t_map			*map;
	void			*mlx;
	t_window		*window;
	t_player		player;
	t_tex			tex;
	t_img			img;
	t_img			bg_img;
	t_npc			**npcs;
	int				npc_count;
	t_door			**doors;
	int				door_count;
	t_dpoint		exit_pos;
	t_item			**items;
	int				item_count;
	t_entity		*entities;
    int				entity_count;
	bool			minimap_visible;
	bool			keys[66000];
	bool			temp_msg_visible;
	char			temp_msg[50];
	double			temp_msg_timer;
	double			fps;
	int				frame_count;
	double			fps_time_acc;
}	t_game;

// UTILS
void	error(t_game *game, char *err_msg);
void	free_game(t_game *game);
void	free_tex_frames(t_game *game, t_texture *frames, int count);
void	free_npc_waypoints(t_npc *npc);
void	free_single_npc(t_game *game, t_npc *npc);
void	free_npcs(t_game *game);
void	free_single_item(t_game *game, t_item *item);
void	free_items(t_game *game);
void	load_single_xpm(t_game *game, t_texture *tex, char *path, void *mlx);
double	get_delta_time(void);
void	draw_lose_message(t_game *game);
void	check_win_condition(t_game *game);
void	draw_win_message(t_game *game);
bool	is_facing_target(t_player *player, t_dpoint target_pos);
void	update_entities_sort(t_game *game);
int		handle_game_state(t_game *game);
void	init_background(t_game *game);

// PARSING
void	extract_file_content(t_game *game, t_map *map);
char	*get_config_value(t_game *game, const char *trimmed, int key_len);
int		process_config(t_game *game, t_map *map, int i, int *map_start);
void	process_color_key(t_game *game, const char *trimmed,
			const char *key, int *dest);
void	normalize_map_layout(t_game *game, t_map *map);
void	calculate_map_dimension(t_game *game, t_map *map);
void	process_map_cell(t_game *game, t_map *map, int row, int col);
void	check_map_boundaries(t_game *game, t_map *map, int row, int col);
void	check_map_chars(t_game *game, char c, int row, int col);
int		convert_map_char_to_value(t_game *game, t_map *map, int i, int j);
void	parse_map(t_game *game, t_map *map);

// INITIALIZATION
t_game	*init_game(char *filename);
void	load_game_textures(t_game *game, t_conf conf);
void	load_sprite_frames_npc(t_game *game, t_sprite *sprite);
void	update_enemy_npc(t_game *game, t_npc *npc, double delta_time);
void	update_all_npcs(t_game *game, double delta_time);
bool	move_npc(t_game *game, t_npc *npc, t_dpoint target, double delta_time);
void	move_npc_patrol(t_game *game, t_npc *npc, double delta_time);
void	move_npc_follow(t_game *game, t_npc *npc, double delta_time);

// TEMP_MESSAGE
void	update_temp_message(t_game *game, double delta_time);
void	show_temp_message(t_game *game, double duration, const char *message);
void	draw_temp_message(t_game *game);

// NPC
void	init_npc_animation(t_game *game, t_sprite *sprite);
void	init_npc_pathfinding(t_game *game, t_npc *npc);
void	generate_npc_waypoints(t_npc *npc, t_game *game);
void	update_npc_list(t_game *game, t_npc *npc);
void	spawn_witch_kitty(t_game *game, double x, double y);
void	spawn_calico_kitty(t_game *game, double x, double y);
int		get_walk_animation_base_index(int walk_block);
int		get_walk_block(t_npc *npc, t_player *player);
void	draw_kitty_npc(t_game *game, t_npc *npc, double *z_buffer);
void	draw_fire_spirit(t_game *game, t_npc *npc, double *z_buffer);
void	play_movement_animation(t_npc *npc, double delta_time);
void	play_wait_animation(t_npc *npc, double delta_time);
void	play_speak_animation(t_npc *npc, double delta_time);
void	play_fire_spirit_idle_animation(t_npc *npc, double delta_time);
void	play_fire_spirit_hit_animation(t_npc *npc, double delta_time);
void	change_fire_spirit_behavior(t_game *game, t_npc *npc);
void	free_npc_textures(t_game *game, t_sprite *sprite);
void	free_npc_waypoints(t_npc *npc);
void	spawn_fire_spirit(t_game *game, double x, double y);
bool	has_line_of_sight(t_game *game, t_dpoint src, t_dpoint target);
void	update_npc_follow_path(t_game *game, t_player *player, t_npc *npc);
void	update_npc(t_game *game, t_npc *npc, double delta_time);

// ITEM
void	spawn_well(t_game *game, double x, double y);
void	spawn_bucket(t_game *game, double x, double y);
void	spawn_tree(t_game *game, double x, double y);
void	spawn_key(t_game *game, double x, double y);
void	update_item_list(t_game *game, t_item *item);
void	update_items(t_game *game, double delta_time);

// DOOR
void	update_doors(t_game *game, double delta_time);
void	update_door_list(t_game *game, t_door *door);
void	spawn_exit_door(t_game *game, double x, double y);
void	spawn_door(t_game *game, double x, double y);
t_door	*find_door_at(t_game *game, t_point pos);
t_door	*find_closest_door(t_game *game, double range);

// RENDERING
void	calculate_texture_mapping(t_game *game, t_ray *ray);
void	calculate_ray_properties(t_game *game, t_ray *ray);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_current_frame(double anim_start, int num_frames,
		int frame_duration_ms);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_dda_ray(t_game *game, t_ray *ray);
void	raycast(t_game *game, t_ray *ray, int *x, double *z_buffer);
void	perform_dda(t_game *game, t_ray *ray);
void	render_scene(t_game *game, double delta_time);
bool	init_sprite_draw_data(t_sprite_draw *data, t_player player,
		t_sprite *sprite);
void	draw_minimap(t_game *game);
void	draw_pause_message(t_game *game);
void	draw_follow_state(t_game *game);
void	draw_npc_dialogue(t_game *game);
void	draw_splash(t_game *game, t_player *player, double delta_time);
void	draw_bucket_state(t_game *game);
void	init_player(t_game *game, t_player *player);
void	set_frame_sizes(t_texture *frames, int count, t_point size);
void	load_sprite_animation(t_game *game, t_texture **frames,
		char **paths, int frame_count);
void	draw_texture(t_game *game, t_texture *texture,
		t_dpoint texture_pos, double *z_buffer);
void	draw_entities(t_game *game, double *z_buffer);
void	draw_key(t_game *game, t_item *item, double *z_buffer);
double	compute_determinant(t_player player);
double	compute_inverse_determinant(double det);
double	compute_transform_x(t_player player, t_dpoint rel, double inv_det);
double	compute_transform_y(t_player player, t_dpoint rel, double inv_det);
bool	is_sprite_in_front(double transform_y);
bool	calc_sprite_screen_coords(t_sprite_draw *data);
void	draw_sprite(t_game *game, t_player player, t_sprite *sprite,
		double *z_buffer);
void	draw_sprite_column(t_game *game, t_sprite_draw *data,
		double *z_buffer);
int		get_tile_size(t_map *map);
t_point	get_minimap_position(t_point map_pos, int tile_size);
bool	is_point_in_circle(t_point offset, int radius);

// HOOKS
bool	interact_with_door(t_game *game);
bool	interact_with_item(t_game *game);
t_npc	*find_closest_npc(t_game *game, double max_distance);
bool	interact_with_npc(t_game *game);
bool	advance_npc_dialogue(t_npc *npc, t_story_state *story);
void	update_story(t_game *game);
bool	handle_npc_chase(t_game *game);
bool	handle_npc_dialogue(t_game *game);
bool	continue_npc_dialogue(t_game *game);
void	handle_interaction(t_game *game);
void	make_closest_npc_follow(t_game *game, double max_distance);
int		pause_game(t_game *game);
void	handle_event_hooks(t_game *game, t_window *window);

// GAME LOOP
int		game_loop(t_game *game);
void	handle_mouse_movement(t_game *game, t_window *window);
bool	is_map_position_valid_player(t_game *game, t_dpoint pos);
bool	is_within_bounds(t_game *game, t_point pos);
bool	is_any_npc_talking(t_game *game);
bool	is_player_move_valid(t_game *game, t_dpoint pos);
bool	is_position_valid_npc(t_game *game, t_npc *npc, t_astar *astar, t_point pos);
bool	is_wall(t_game *game, t_point pos);
void	handle_player_moves(t_game *game, double delta_time);
void	rotate_player_left(t_player *player, double delta_time);
void	rotate_player_right(t_player *player, double delta_time);
void	move_player_forward(t_game *game, t_player *player,
		double delta_time);
void	move_player_backward(t_game *game, t_player *player,
		double delta_time);
void	strafe_player_left(t_game *game, t_player *player,
		double delta_time);
void	strafe_player_right(t_game *game, t_player *player,
		double delta_time);

// A_STAR_SEARCH
void	closed_list_insert(t_closed_list *closed_list, t_node *node,
			t_game *game);
t_node	*closed_list_extract_min(t_closed_list *closed_list);
void	reconstruct_path(t_game *game, t_node *goal_node, t_npc *npc);
void	setup_astar_struct(t_game *game, t_astar *astar, t_point start,
			t_point goal);
void	spread_child_node(t_game *game, t_npc *npc, t_astar *astar);
void	reset_astar_struct(t_game *game, t_astar *astar);
void	a_star_path(t_game *game, t_npc *npc, t_point start, t_point goal);
void	handle_event_hooks(t_game *game, t_window *window);

// MEMORY UTILS
void	*x_malloc(t_game *game, size_t size);
void	*x_calloc(t_game *game, size_t count, size_t size);
void	*x_realloc(t_game *game, void *ptr, size_t old_size, size_t new_size);
char	*x_strjoin_free(t_game *game, char *s1, char *s2);
char	*x_strdup(t_game *game, const char *s);
char	**x_copy_strarray(t_game *game, char **array);
int		**x_create_matrix(t_game *game, int row_count, int col_count);
char	*x_itoa(t_game *game, int n);

t_dial_phase	get_witch_kitty_phase(t_story_state *story);
t_dial_phase	get_calico_phase(t_story_state *story);
t_dial_phase	get_fire_spirit_phase(t_story_state *story);
void			allocate_dialogues(t_game *game, t_dial *dialog,
				char *dialogues[][11], int phase_count);
void			update_npc_story(t_game *game, t_npc *calico, t_npc *witch,
				t_npc *fire_spirit);

// MUSIC
void	start_background_music(const char *music_file);
void	stop_background_music(void);

#endif