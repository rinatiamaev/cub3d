/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:08:40 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/04 20:08:06 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

# include <mlx.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>

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

# define UP			122
# define DOWN		115
# define LEFT		113
# define RIGHT		100
# define ARR_RIGHT	65363
# define ARR_LEFT	65361
# define PAUSE		32
# define ESC		65307

# define WIN_NAME	"Cube3D"
# define WIN_W		1200
# define WIN_H		900

# define TEX_W		128
# define TEX_H		128

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
	double		rot_speed;	// Rotation speed per frame
	double		move_speed;	// Movement speed per frame
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
	bool		is_paused;
	bool		keys[66000];
}	t_game;

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
void	load_textures(t_game *game, t_conf conf);
int		close_game(t_game *game);
void	calculate_ray_properties(t_game *game, t_ray *ray);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_tex_color(t_texture *tex, int x, int y);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_dda_ray(t_game *game, t_ray *ray);
void	render_scene(t_game *game);
int		game_loop(t_game *game);
int		pause_game(t_game *game);
void	handle_event_hooks(t_game *game, t_window *window);
void	handle_player_moves(t_game *game);
void	rotate_left(t_player *player, double rot_speed);
void	rotate_right(t_player *player, double rot_speed);

void	*x_calloc(t_game *game, size_t count, size_t size);
char	*x_strjoin_free(t_game *game, char *s1, char *s2);
char	*x_strdup(t_game *game, const char *s);
char	**x_copy_strarray(t_game *game, char **array);
int		**x_create_matrix(t_game *game, int row_count, int col_count);

#endif