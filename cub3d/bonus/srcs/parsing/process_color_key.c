/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_color_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:02:22 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 20:55:21 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	process_color_key(t_game *game, const char *trimmed,
	const char *key, int *dest)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	if (*dest != -1)
		error(game, "Duplicate config key");
	*dest = parse_color(game, get_config_value(game, trimmed, key_len));
}
