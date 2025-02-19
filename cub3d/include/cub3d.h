/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:08:40 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 09:40:01 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "asset_path.h"

# include <mlx.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>

# define WIN_NAME	"Cube3d"
# define WIN_W	1600
# define WIN_H	1200

# define TEXT_W 128
# define TEXT_H 128

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_conf
{
	char	*text_no;
	char	*text_so;
	char	*text_we;
	char	*text_ea;
	int		floor_color;
	int		ceiling_color;
} t_conf;

typedef struct s_map
{
	int		fd;
	char	*filename;
	char	**file_content;
	t_conf	conf;
	char	**map_layout;
	int		row_count;
	int		max_width;
	int		player_count;
	int		**matrix;
}	t_map;

typedef struct s_window
{
	void	*ptr;
	char	*name;
	t_point	size;
}	t_window;

typedef struct s_player
{
	t_point	pos;
	char	dir;
}	t_player;

typedef struct s_img
{
	t_point		size;
	void		*no_wall;
	void		*so_wall;
	void		*we_wall;
	void		*ea_wall;
}	t_img;

typedef struct s_game
{
	t_map		*map;
	void		*mlx;
	t_window	*window;
	t_player	player;
	t_img		img;
}	t_game;

t_game	*init_game(char *filename);
void	error(t_game *game, char *err_msg);
void	free_game(t_game *game);
void	parse_map(t_game *game, t_map *map);

void	*x_calloc(t_game *game, size_t count, size_t size);
char	*x_strjoin_free(t_game *game, char *s1, char *s2);
char	*x_strdup(t_game *game, const char *s);
char	**x_copy_strarray(t_game *game, char **array);
int		**x_create_matrix(t_game *game, int row_count, int col_count);

#endif