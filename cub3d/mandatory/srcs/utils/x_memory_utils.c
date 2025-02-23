/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_memory_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:12:24 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/19 19:58:59 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*x_calloc(t_game *game, size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		error(game, "ft_calloc() failed");
	return (ptr);
}

char	*x_strjoin_free(t_game *game, char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (!joined)
	{
		free(s1);
		free(s2);
		error(game, "ft_strjoin() failed");
	}
	free(s1);
	free(s2);
	return (joined);
}

char	*x_strdup(t_game *game, const char *s)
{
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
		error(game, "ft_strdup() failed");
	return (dup);
}

char	**x_copy_strarray(t_game *game, char **array)
{
	char	**copy;

	copy = ft_copy_strarray(array);
	if (!copy)
		error(game, "ft_copy_strarray() failed");
	return (copy);
}

int	**x_create_matrix(t_game *game, int row_count, int col_count)
{
	int	**matrix;

	matrix = ft_create_matrix(row_count, col_count);
	if (!matrix)
		error(game, "ft_create_matrix() failed");
	return (matrix);
}
