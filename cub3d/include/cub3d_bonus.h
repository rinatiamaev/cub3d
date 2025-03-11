/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:08:40 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/11 22:35:48 by nlouis           ###   ########.fr       */
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

# define MINIMAP_SIZE		250
# define MINIMAP_OFFSET_X	20
# define MINIMAP_OFFSET_Y	20
# define PLAYER_SCALE		0.6
# define WALL_COLOR			0xFFFFFF	// White walls
# define PLAYER_COLOR		0xFFFF00	// Yellow player

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

# define UP				122
# define DOWN			115
# define LEFT			113
# define RIGHT			100
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

# define M_PI		3.14159265358979323846
# define DEAD_ZONE	1.0

# define MAX_LINE_LENGTH	40
# define MAX_LINES			4

typedef enum e_char_value
{
	FREE_SPACE,
	WALL,
	CONF_DIR,
	EMPTY,
	WITCH_KITTY,
	CALICO_KITTY,
	FIRE_SPIRIT,
	DOOR
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

typedef struct s_player
{
	char		conf_dir;
	t_dpoint	pos;		// (x, y) in double precision
	t_dpoint	last_pos;
	t_dpoint	dir;		// Direction vector: which way is "forward"
	t_dpoint	plane;		// Camera plane vector: perpendicular to dir
	double		rot_speed;	// Rotation speed in radians per second
	double		move_speed;	// Movement speed per frame
	double		angle;		// Player’s facing angle (in radians)
	bool		has_water;
}	t_player;

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
	double		transform_x;			// Sprite X in camera space
	double		transform_y;			// Sprite Y in camera space
	int			screen_x;				// X coordinate of sprite center screen
	int			height;					// Calculated sprite height on screen
	int			width;					// Calculated sprite width on screen
	t_point		draw_start;				// (top-left) of sprite bounding box
	t_point		draw_end;				// (bott-right) of sprite bounding box
	int			current_frame;			// Chosen animation frame
	t_texture	*texture;				// Pointer to the sprite texture
	t_point		texture_size;			// (width, height) of the sprite tex
	int			stripe_x;				// Current vert stripe in screen space
	int			texture_x;				// Corresponding x in the sprite tex
	int			y;						// Loop index for screen Y
	int			d;						// Helper for fixed-point texture Y
	int			texture_y;				// Corresponding y in the sprite tex
	int			color;					// Final color from texture
}	t_sprite_draw;

typedef enum e_npc_state
{
	WAIT,
	PATROL,
	FOLLOW,
	SPEAK,
	CHASE,
	HIT
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
	int			num_idle_frames;
	char		**move_paths;
	t_texture	*move_frames;
	int			move_frames_count;
	char		**speak_paths;
	t_texture	*speak_frames;
	int			speak_frames_count;
	char		**hit_paths;
	t_texture	*hit_frames;
	int			hit_frames_count;
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

typedef struct s_npc
{
	char		*type;
	t_dpoint	pos;
	t_npc_state	state;
	double		speed;
	t_dpoint	move_vec;
	t_dpoint	last_move_vec;
	t_sprite	sprite;
	t_astar		*astar;
	char		**lines;
	int			line_count;
	int			current_line;
	int			patrol_range;
	t_dpoint	*waypoints;
	int			waypoint_count;
	int			current_wp;
	t_dpoint	*path;
	int			path_length;
	int			path_index;
	double		threshold_dist;
	bool		is_following;
	bool		is_enemy;
	bool		is_hit;
}	t_npc;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

typedef struct s_door
{
	t_dpoint		pos;		// Door grid position
	double			offset;		// Sliding offset
	t_door_state	state;		// Door current state
	double			speed;		// How fast the door opens/closes
	double			open_timer;	// Time the door stays open after fully opening
}	t_door;

typedef struct s_tex
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	t_texture	door;
	t_texture	dialogue_box;
}	t_tex;

typedef enum e_game_state
{
	RUNNING,
	PAUSED,
	GAME_OVER
}	t_game_state;

typedef struct s_game
{
	t_game_state	state;
	t_map			*map;
	void			*mlx;
	t_window		*window;
	t_player		player;
	t_tex			tex;
	t_img			img;
	t_npc			**npcs;
	int				npc_count;
	t_door			**doors;
	int				door_count;
	bool			minimap_visible;
	bool			keys[66000];
}	t_game;

// UTILS
void	error(t_game *game, char *err_msg);
void	free_game(t_game *game);
void	free_single_npc(t_game *game, t_npc *npc);
void	free_npcs(t_game *game);
double	get_delta_time(void);
void	draw_lose_message(t_game *game);

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
void	load_sprite_frames(t_game *game, t_sprite *sprite);
void	update_enemy_npc(t_game *game, t_npc *npc, double delta_time);
void	update_all_npcs(t_game *game, double delta_time);
void	draw_sprite(t_game *game, t_player player, t_sprite *sprite,
			double *z_buffer);
bool	move_npc(t_game *game, t_npc *npc, t_dpoint target, double delta_time);
void	move_npc_patrol(t_game *game, t_npc *npc, double delta_time);
void	move_npc_follow(t_game *game, t_npc *npc, double delta_time);

// NPC
void	init_sprite_frames_and_animation(t_game *game, t_sprite *sprite);
void	generate_npc_waypoints(t_npc *npc, t_game *game);
void	update_npc_list(t_game *game, t_npc *npc);
void	spawn_witch_kitty(t_game *game, double x, double y);
void	spawn_calico_kitty(t_game *game, double x, double y);
int		get_walk_block(t_npc *npc, t_player *player);
void	draw_kitty_npc(t_game *game, t_npc *npc, double *z_buffer);
void	draw_fire_spirit(t_game *game, t_npc *npc, double *z_buffer);
void	play_movement_animation(t_npc *npc, double delta_time);
void	play_wait_animation(t_npc *npc, double delta_time);
void	play_speak_animation(t_npc *npc, double delta_time);
void	play_fire_spirit_idle_animation(t_npc *npc, double delta_time);
void	play_fire_spirit_hit_animation(t_npc *npc, double delta_time);
bool	is_position_occupied_by_npc(t_game *game, t_point pos);
void	change_fire_spirit_behavior(t_game *game, t_npc **npc);
void	spawn_fire_spirit(t_game *game, double x, double y);
bool	has_line_of_sight(t_game *game, t_dpoint src, t_dpoint target);

// DOOR
void	update_doors(t_game *game, double delta_time);
void	spawn_door(t_game *game, double x, double y);
t_door	*find_door_at(t_game *game, t_point pos);

// RENDERING
void	calculate_texture_mapping(t_game *game, t_ray *ray);
void	calculate_ray_properties(t_game *game, t_ray *ray);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_tex_color(t_texture *tex, int x, int y);
int		get_current_frame(double anim_start, int num_frames,
			int frame_duration_ms);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_dda_ray(t_game *game, t_ray *ray);
void	fill_ceiling_and_floor(t_img *img, int ceiling_color,
			int floor_color);
void	raycast(t_game *game, t_ray *ray, int *x, double *z_buffer);
void	perform_dda(t_game *game, t_ray *ray);
void	render_scene(t_game *game);
bool	init_sprite_draw_data(t_sprite_draw *data, t_player player,
			t_sprite *sprite);
void	draw_npcs(t_game *game, double *z_buffer);
void	draw_minimap(t_game *game);
void	draw_follow_state(t_game *game);
void	draw_npc_dialogue(t_game *game);

// HOOKS
bool	interact_with_door(t_game *game);
t_npc	*find_closest_npc(t_game *game, double max_distance);
bool	interact_with_npc(t_game *game);
bool	advance_npc_dialogue(t_npc *npc);
void	handle_interaction(t_game *game);
void	make_closest_npc_follow(t_game *game, double max_distance);
int		pause_game(t_game *game);
void	handle_event_hooks(t_game *game, t_window *window);

// GAME LOOP
int		game_loop(t_game *game);
void	handle_mouse_movement(t_game *game, t_window *window);
bool	can_move(t_game *game, double next_x, double next_y);
void	handle_player_moves(t_game *game);
void	rotate_left(t_player *player, double rot_speed, double delta_time);
void	rotate_right(t_player *player, double rot_speed, double delta_time);
void	handle_player_defeat(t_game *game);

// A_STAR_SEARCH
void	closed_list_insert(t_closed_list *closed_list, t_node *node,
			t_game *game);
t_node	*closed_list_extract_min(t_closed_list *closed_list);
void	reconstruct_path(t_game *game, t_node *goal_node, t_npc *npc);
void	setup_astar_struct(t_game *game, t_astar *astar, t_point start,
			t_point goal);
void	spread_child_node(t_game *game, t_astar *astar);
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

// MUSIC
void	start_background_music(const char *music_file);
void	stop_background_music(void);

#endif