/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:06:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 20:55:25 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*get_config_value(t_game *game, const char *trimmed, int key_len)
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

static void	parse_config_line(t_game *game, t_map *map, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed || trimmed[0] == '\0')
		;
	else if (ft_strncmp(trimmed, "NO", 2) == 0)
		process_texture_key(game, trimmed, "NO", &map->conf.tex_no);
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		process_texture_key(game, trimmed, "SO", &map->conf.tex_so);
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		process_texture_key(game, trimmed, "WE", &map->conf.tex_we);
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		process_texture_key(game, trimmed, "EA", &map->conf.tex_ea);
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

int	process_config(t_game *game, t_map *map, int i, int *map_start)
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
