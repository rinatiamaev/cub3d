/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_config_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:06:34 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:14:57 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Extracts the configuration value from a trimmed config line.
 *
 * This function is used to retrieve the value part of a configuration line
 * after the key ("NO", "F"...). It first checks that the character
 * immediately following the key is a space or tab. If not, the format is
 * invalid.
 *
 * It then skips any additional whitespace to reach the actual value (e.g.,
 * a path to a texture or an RGB color string). If no valid value is found,
 * the function triggers a fatal error.
 *
 * @param game Pointer to the game context, used for error handling.
 * @param trimmed The configuration line, already trimmed of outer whitespace.
 * @param key_len Length of the key (used to extract the value part).
 * @return Pointer to the start of the value within the trimmed line.
 */
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

/**
 * @brief Processes a texture configuration key and stores the associated path.
 *
 * This function handles parsing of texture keys such as "NO", "SO", "WE", "EA".
 * It ensures that the key is not already set to prevent duplicates, checks that
 * the texture path ends with ".xpm", and stores the path in the corresponding
 * destination pointer.
 *
 * @param game Pointer to the game context, used for memory/error handling.
 * @param trimmed Trimmed configuration line starting with the key.
 * @param key The key string (e.g. "NO", "SO").
 * @param dest Pointer to the string where the texture path should be stored.
 */
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

/**
 * @brief Parses a single configuration line from the map file.
 *
 * Determines whether the line defines a texture path or a color. Delegates
 * parsing to either `process_texture_key()` or `process_color_key()` based
 * on the prefix of the trimmed line. If the line doesn't match a known key,
 * it raises an error.
 *
 * @param game Pointer to the game context.
 * @param map Pointer to the map structure where config will be stored.
 * @param line Raw line from the map file to be parsed.
 */
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

/**
 * @brief Checks if a line starts with a known configuration key.
 *
 * Recognized keys include texture identifiers ("N", "S", "W", "E") and
 * color definitions ("F", "C"). This check helps distinguish between
 * config lines and map layout lines during parsing.
 *
 * @param line The line to check.
 * @return 1 if the line is a configuration line, 0 otherwise.
 */
static int	is_config_line(const char *line)
{
	return (line[0] == 'N' || line[0] == 'S'
		|| line[0] == 'W' || line[0] == 'E'
		|| line[0] == 'F' || line[0] == 'C');
}

/**
 * @brief Processes a single line of the map file configuration section.
 *
 * This function trims the line and checks if it matches a configuration
 * key. If so, it parses the config using `parse_config_line()`. If not,
 * it assumes the line is the start of the map layout and sets `map_start`
 * accordingly. It returns 1 to continue parsing config, or 0 to switch to
 * parsing the map layout.
 *
 * @param game Pointer to the game context.
 * @param map Pointer to the map structure.
 * @param i Current line index in map->file_content.
 * @param map_start Pointer to the integer where the layout start index is set.
 * @return 1 if the line was part of config, 0 if map layout has started.
 */
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
