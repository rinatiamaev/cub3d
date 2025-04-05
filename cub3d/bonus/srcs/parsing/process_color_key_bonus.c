/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_color_key_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:02:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:12:35 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Extracts a color component from a string and converts it to an int.
 *
 * This function trims whitespace from the input string, checks if it's a valid
 * integer, and converts it to an integer. If the conversion fails or the value
 * is out of range (0-255), an error is raised.
 *
 * @param game Pointer to the game context (for error handling).
 * @param part The string containing the color component.
 * @return The integer value of the color component.
 */
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

/**
 * @brief Parses an RGB color string into an integer representation.
 *
 * This function expects a string in the format "R,G,B", where R, G, and B
 * are integers in the range [0, 255]. It splits the string using commas,
 * validates that there are exactly 3 components, and ensures each is
 * numeric and within the valid range.
 *
 * Each component is extracted using `get_color_component()`, which performs
 * trimming and numeric validation. The final RGB value is encoded as a
 * 24-bit integer using bit-shifting:
 *
 *     result = (r << 16) | (g << 8) | b
 *
 *
 * @param game Pointer to the game context (used for error handling).
 * @param color_str The string containing the color definition.
 * @return Encoded RGB value as an int (0xRRGGBB).
 */
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

/**
 * @brief Processes and stores a color configuration value from a config line.
 *
 * This function extracts and validates a color value (R,G,B) from a given
 * line in the configuration file. It ensures the key is not duplicated by
 * checking if the destination value is still unset (-1). The function then
 * retrieves the value substring after the key and parses it into a 24-bit
 * integer using `parse_color()`.
 *
 * The result is stored in the memory pointed to by `dest`. If the key is
 * already set or parsing fails, it reports an error and exits.
 *
 * @param game Pointer to the game context for error reporting.
 * @param trimmed The full line containing the key and color value.
 * @param key The expected configuration key (e.g., "F" or "C").
 * @param dest Pointer to the destination variable for storing the result.
 */
void	process_color_key(t_game *game, const char *trimmed,
	const char *key, int *dest)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	if (*dest != -1)
		error(game, "Duplicate config key");
	*dest = parse_color(game, get_config_value(game, trimmed, key_len));
}
