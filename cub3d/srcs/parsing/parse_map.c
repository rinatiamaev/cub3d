/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:06:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 10:38:23 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	extract_file_content(t_game *game, t_map *map)
{
	size_t	len;
	char	*line;
	char	*file;

	file = x_calloc(game, 1, sizeof(char));
	len = ft_strlen(map->filename);
	if (len < 4 || ft_strncmp(map->filename + len - 4, ".cub", 4))
		error(game, "File should have .cub extension");
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd < 0)
		error(game, "open() failed");
	line = get_next_line(map->fd);
	while (line != NULL)
	{
		file = x_strjoin_free(game, file, line);
		line = get_next_line(map->fd);
	}
	free(line);
	if (errno == ENOMEM)
		error(game, "get_next_line() failed");
	close(map->fd);
	map->file_content = ft_split(file, '\n');
	if (!map->file_content)
		error(game, "ft_split() failed");
	free(file);
}

static int	get_color_component(t_game *game, char *part)
{
	char	*token;
	int		value;

	token = ft_strtrim(part, " \t");
	if (!token || !ft_is_valid_integer(token))
	{
		free(token);
		error(game, "Invalid color value: non-numeric token");
	}
	value = ft_atoi(token);
	free(token);
	return (value);
}

static int	parse_color(t_game *game, const char *color_str)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = ft_split(color_str, ',');
	if (!parts)
		error(game, "ft_split() failed");
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		ft_free_array((void **)parts);
		error(game, "Invalid color format");
	}
	r = get_color_component(game, parts[0]);
	g = get_color_component(game, parts[1]);
	b = get_color_component(game, parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_array((void **)parts);
		error(game, "Color value out of range");
	}
	ft_free_array((void **)parts);
	return ((r << 16) | (g << 8) | b);
}

static char	*get_config_value(t_game *game, const char *trimmed, int key_len)
{
	char	*value;

	if (trimmed[key_len] != ' ' && trimmed[key_len] != '\t')
		error(game, "Invalid config format");
	value = skip_whitespace_ptr(trimmed + key_len);
	if (!value || value[0] == '\0')
		error(game, "Invalid config format");
	return (value);
}

static void	process_texture_key(t_game *game, const char *trimmed,
	const char *key, char **dest)
{
	size_t	key_len;
	int		len;

	key_len = ft_strlen(key);
	if (*dest != NULL)
		error(game, "Duplicate config key");
	len = ft_strlen(trimmed);
	if (len < 4 || ft_strncmp(trimmed + len - 4, ".xpm", 4))
		error(game, "Texture should have .xpm extension");
	*dest = x_strdup(game, get_config_value(game, trimmed, key_len));
}

static void	process_color_key(t_game *game, const char *trimmed,
	const char *key, int *dest)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	if (*dest != -1)
		error(game, "Duplicate config key");
	*dest = parse_color(game, get_config_value(game, trimmed, key_len));
}

static void	parse_config_line(t_game *game, t_map *map, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed || trimmed[0] == '\0')
		;
	else if (ft_strncmp(trimmed, "NO", 2) == 0)
		process_texture_key(game, trimmed, "NO", &map->conf.text_no);
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		process_texture_key(game, trimmed, "SO", &map->conf.text_so);
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		process_texture_key(game, trimmed, "WE", &map->conf.text_we);
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		process_texture_key(game, trimmed, "EA", &map->conf.text_ea);
	else if (ft_strncmp(trimmed, "F", 1) == 0)
		process_color_key(game, trimmed, "F", &map->conf.floor_color);
	else if (ft_strncmp(trimmed, "C", 1) == 0)
		process_color_key(game, trimmed, "C", &map->conf.ceiling_color);
	else
	{
		free(trimmed);
		error(game, "Unknown config key");
	}
	free(trimmed);
}

static int	is_config_line(const char *line)
{
	return (line[0] == 'N' || line[0] == 'S'
		|| line[0] == 'W' || line[0] == 'E'
		|| line[0] == 'F' || line[0] == 'C');
}

static int	process_config(t_game *game, t_map *map, int i, int *map_start)
{
	char	*trim_line;

	trim_line = ft_strtrim(map->file_content[i], " \t");
	if (!trim_line || trim_line[0] == '\0')
	{
		free(trim_line);
		return (1);
	}
	if (is_config_line(trim_line))
		parse_config_line(game, map, map->file_content[i]);
	else
	{
		*map_start = i;
		free(trim_line);
		return (0);
	}
	free(trim_line);
	return (1);
}

static void	validate_config(t_game *game, t_map *map)
{
	if (!map->conf.text_no || !map->conf.text_so
		|| !map->conf.text_we || !map->conf.text_ea)
		error(game, "Missing texture configuration");
	if (map->conf.floor_color == -1 || map->conf.ceiling_color == -1)
		error(game, "Missing color configuration");
}

static void	check_map_chars(t_game *game, char c, int row, int col)
{
	if (!ft_strchr(" 012NSEW", c))
		error(game, "Invalid character in map layout");
	if (ft_strchr("NSEW", c))
	{
		game->player.pos.x = col;
		game->player.pos.y = row;
		game->player.conf_dir = c;
		game->map->player_count++;
	}
}

static void	check_map_boundaries(t_game *game, t_map *map, int row, int col)
{
	if (row == 0 || row == map->row_count - 1
		|| col == 0 || col == map->max_width - 1)
		error(game, "Map is not closed (cell on boundary)");
	if (map->map_layout[row - 1][col] == ' '
		|| map->map_layout[row + 1][col] == ' '
		|| (col > 0 && map->map_layout[row][col - 1] == ' ')
		|| (col + 1 < (int)ft_strlen(map->map_layout[row])
		&& map->map_layout[row][col + 1] == ' '))
		error(game, "Map is not closed (cell adjacent to void)");
}

static void	process_map_cell(t_game *game, t_map *map, int row, int col)
{
	char	c;

	c = map->map_layout[row][col];
	check_map_chars(game, c, row, col);
	if (c == '0' || ft_strchr("NSEW", c))
		check_map_boundaries(game, map, row, col);
}

static void	calculate_map_dimension(t_game *game, t_map *map)
{
	int	i;
	int	current_length;

	map->row_count = ft_arraysize((void **)map->map_layout);
	if (map->row_count == 0)
		error(game, "Map layout is empty");
	i = 0;
	while (map->map_layout[i])
	{
		current_length = ft_strlen(map->map_layout[i]);
		if (current_length > map->max_width)
			map->max_width = current_length;
		i++;
	}
}

static void	normalize_map_layout(t_game *game, t_map *map)
{
	int		row;
	int		len;
	char	*new_line;

	row = 0;
	while (row < map->row_count)
	{
		len = ft_strlen(map->map_layout[row]);
		if (len < map->max_width)
		{
			new_line = x_calloc(game, map->max_width + 1, sizeof(char));
			ft_memcpy(new_line, map->map_layout[row], len);
			while (len < map->max_width)
			{
				new_line[len] = ' ';
				len++;
			}
			free(map->map_layout[row]);
			map->map_layout[row] = new_line;
		}
		row++;
	}
}

static void	parse_map_layout(t_game *game, t_map *map)
{
	int	row;
	int	col;

	calculate_map_dimension(game, map);
	normalize_map_layout(game, map);
	row = 0;
	while (row < map->row_count)
	{
		col = 0;
		while (col < (int)ft_strlen(map->map_layout[row]))
		{
			process_map_cell(game, map, row, col);
			col++;
		}
		row++;
	}
	if (map->player_count != 1)
		error(game, "Map must have exactly one player starting position");
}

static void	parse_content(t_game *game, t_map *map)
{
	int	i;
	int	map_start;

	i = 0;
	map_start = -1;
	while (map->file_content[i])
	{
		if (!process_config(game, map, i, &map_start))
			break ;
		i++;
	}
	if (map_start == -1)
		error(game, "No map layout found in file");
	validate_config(game, map);
	map->map_layout = x_copy_strarray(game, map->file_content + map_start);
	parse_map_layout(game, map);
}

static void	map_layout_to_matrix(t_game *game, t_map *map)
{
	int	i;
	int	j;

	map->matrix = x_create_matrix(game, map->row_count, map->max_width);
	i = 0;
	while (i < map->row_count)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map_layout[i]))
		{
			if (map->map_layout[i][j] == '1')
				map->matrix[i][j] = 1;
			else if (ft_strchr("NSEW", map->map_layout[i][j]))
				map->matrix[i][j] = 2;
			else if (map->map_layout[i][j] == '0')
				map->matrix[i][j] = 0;
			else
				map->matrix[i][j] = 3;
			j++;
		}
		i++;
	}
}

void	parse_map(t_game *game, t_map *map)
{
	extract_file_content(game, map);
	parse_content(game, map);
	map_layout_to_matrix(game, map);
}
