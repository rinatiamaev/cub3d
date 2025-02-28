/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:06:01 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/01 01:44:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	validate_config(t_game *game, t_map *map)
{
	if (!map->conf.tex_no || !map->conf.tex_so
		|| !map->conf.tex_we || !map->conf.tex_ea)
		error(game, "Missing texture configuration");
	if (map->conf.floor_color == -1 || map->conf.ceiling_color == -1)
		error(game, "Missing color configuration");
}

static void	parse_map_layout(t_game *game, t_map *map)
{
	int	row;
	int	col;

	calculate_map_dimension(game, map);
	normalize_map_layout(game, map);
	row = 0;
	while (row < map->size.y)
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

	map->matrix = x_create_matrix(game, map->size.y, map->size.x);
	i = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map_layout[i]))
		{
			map->matrix[i][j] = convert_map_char_to_value(game, map, i, j);
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
