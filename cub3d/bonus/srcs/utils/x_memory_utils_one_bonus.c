/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_memory_utils_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:12:24 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 19:50:29 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	*x_calloc(t_game *game, size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		error(game, "ft_calloc() failed");
	return (ptr);
}

void	*x_realloc(t_game *game, void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_realloc(ptr, old_size, new_size);
	if (!new_ptr && new_size > 0)
		error(game, "ft_realloc() failed");
	return (new_ptr);
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

void	*x_malloc(t_game *game, size_t size)
{
	char	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error(game, "malloc() failed");
	return (ptr);
}
