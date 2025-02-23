/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:08:40 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/21 14:59:35 by nlouis           ###   ########.fr       */
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


// # define MINIMAP_SIZE 200    // Size of the minimap (200x200)
// # define MINIMAP_OFFSET_X 100 // Horizontal offset for the minimap (right corner)
// # define MINIMAP_OFFSET_Y 50  // Vertical offset for the minimap (top)
// # define PLAYER_COLOR 0xFF0000  // Color for the player (red)
// # define WALL_COLOR 0x0000FF    // Color for the walls (blue)
# define FLOOR_COLOR 0x00FF00   // Color for the floor (green)

#define MINIMAP_SIZE 150
#define MINIMAP_OFFSET_X 20
#define MINIMAP_OFFSET_Y 20
#define WALL_SCALE 0.6
#define PLAYER_SCALE 0.8 

// Colors (ARGB format for transparency)
#define BACKGROUND_COLOR 0x55332200 // Brown transparent background
#define WALL_COLOR 0xFFFFFF // White walls
#define PLAYER_COLOR 0xFFFF00 // Yellow player
#define TRANSPARENCY 0x33000000 // Extra transparency


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

# define UP				122
# define DOWN			115
# define LEFT			100
# define RIGHT			113
# define ARR_RIGHT		65361
# define ARR_LEFT		65363
# define PAUSE			32
# define ESC			65307
# define TOGGLE_MINIMAP	109

# define WIN_NAME	"Cube3d"
# define WIN_W		1200
# define WIN_H		900

# define TEX_W		128
# define TEX_H		128


# define M_PI 3.14159265358979323846

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

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
	t_dpoint	dir;		// Direction vector: which way is "forward"
	t_dpoint	plane;		// Camera plane vector: perpendicular to dir
	double		rot_speed;	// Rotation speed in radians per second
	double		move_speed;	// Movement speed per frame
	double		angle;		// Player’s facing angle (in radians)
}	t_player;

typedef struct s_texture
{
	void	*ptr;		// The MLX image pointer for this texture
	char	*addr;		// Raw address of the texture data
	t_point	size;		// Texture size (pixels)
	int		bpp;		// Bits per pixel
	int		line_size;	// Number of bytes in one row of the texture
	int		endian;		// 0 = little-endian, 1 = big-endian
}	t_texture;

typedef struct s_sprite_draw_ctx
{
	t_point	step;				// Step size for iterating through the texture (X and Y)
	t_point	tex;				// Current texture coordinates (X and Y)
	int		current_screen_x;	// Current column on the screen where the sprite pixel is drawn
	int		tex_pos_y;			// Vertical position in the texture (used for sampling pixels)
	int		color;				// Color of the current pixel being drawn
}	t_sprite_draw_ctx;

typedef struct s_sprite_props
{
	t_dpoint	transform;	// Transformed NPC coordinates (camera space)
	t_point		screen;		// Sprite screen coordinates
	t_point		size;		// Sprite size (pixels)
	double		depth;		// Depth (transform.y), used for occlusion
}	t_sprite_props;

typedef struct s_npc
{
	t_dpoint	pos;			// NPC world position
	t_texture	*idle_frames;	// Array of textures for idle animation
	int			num_frames;		// Number of frames in the idle animation
	long		anim_start;		// Timestamp (in microseconds) when animation started
}	t_npc;

typedef struct s_tex
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
}	t_tex;

typedef struct s_img
{
	void	*ptr;		// The MLX image pointer for the *frame buffer*
	char	*addr;		// Pointer to the image buffer
	int		bpp;		// Bits per pixel
	int		line_size;	// Number of bytes in one line of the *frame buffer*
	int		endian;		// 0 = little-endian, 1 = big-endian
}	t_img;

typedef struct s_ray
{
	t_dpoint	dir;			// Ray direction
	t_point		map;			// Map square coordinates
	t_dpoint	delta_dist;		// Distance to next side in x and y
	t_dpoint	side_dist;		// Initial distance to next x or y side
	t_point		step_dir;		// Step direction in x and y (+1 or -1)
	bool		hit;			// 1 if a wall was hit
	int			side;			// 0 for vertical side, 1 for horizontal side
	double		perp_w_dist;	// Perpendicular distance from player to wall
	int			line_height;	// Height of wall line to draw
	int			draw_start;		// Starting pixel for wall line
	int			draw_end;		// Ending pixel for wall line
	double		wall_x;			// Exact wall hit position (for texture mapping)
	t_point		tex;			// Texture coordinates 
	double		step;			// How much to increase texture coordinate
	double		tex_pos;		// Initial texture coordinate position
}	t_ray;

typedef struct s_game
{
	t_map		*map;
	void		*mlx;
	t_window	*window;
	t_player	player;
	t_tex		tex;
	t_img		img;
	t_npc		*witch_kitty;
	bool		is_paused;
	bool		minimap_visible;
	bool		keys[66000];
}	t_game;

typedef struct s_minimap
{
    int tile_w; // Tile width
    int tile_h; // Tile height
    int wall_size; // Wall size
    int wall_offset; // Centering walls
    int player_radius; // Player radius
} t_minimap;

void draw_minimap(t_game *game);
t_game	*init_game(char *filename);
void	error(t_game *game, char *err_msg);
void	free_game(t_game *game);
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
void	parse_map(t_game *game, t_map *map);
void	load_walls(t_game *game, t_conf conf);
void	load_textures_array(t_game *game, t_texture *tex_array, int n, char **paths);
int		close_game(t_game *game);
void	calculate_ray_properties(t_game *game, t_ray *ray);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_tex_color(t_texture *tex, int x, int y);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_dda_ray(t_game *game, t_ray *ray);
void	draw_npc(t_game *game, t_npc *npc, double *z_buffer);
void	render_scene(t_game *game);
int		game_loop(t_game *game);
int		pause_game(t_game *game);
void	handle_event_hooks(t_game *game, t_window *window);
void	handle_player_moves(t_game *game);
void	rotate_left(t_player *player, double rot_speed, double delta_time);
void	rotate_right(t_player *player, double rot_speed, double delta_time);

void	*x_calloc(t_game *game, size_t count, size_t size);
char	*x_strjoin_free(t_game *game, char *s1, char *s2);
char	*x_strdup(t_game *game, const char *s);
char	**x_copy_strarray(t_game *game, char **array);
int		**x_create_matrix(t_game *game, int row_count, int col_count);

#endif