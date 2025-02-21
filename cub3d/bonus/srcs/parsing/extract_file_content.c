/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:58:09 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/20 20:55:10 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	extract_file_content(t_game *game, t_map *map)
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
