/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_memory_utils_one_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:12:24 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/04 12:02:32 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Allocates zero-initialized memory or exits on failure.
 *
 * Wraps ft_calloc and handles allocation failure by invoking error().
 *
 * @param game Pointer to the game context (used in case of error).
 * @param count Number of elements to allocate.
 * @param size Size of each element.
 * @return Pointer to allocated memory.
 */
void	*x_calloc(t_game *game, size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		error(game, "ft_calloc() failed");
	return (ptr);
}

/**
 * @brief Reallocates memory with error handling.
 *
 * Wraps ft_realloc and exits if allocation fails and new_size is non-zero.
 *
 * @param game Pointer to the game context (used in case of error).
 * @param ptr Pointer to the previously allocated memory.
 * @param old_size Size of the old memory block.
 * @param new_size Desired size of the new memory block.
 * @return Pointer to newly allocated memory.
 */
void	*x_realloc(t_game *game, void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_realloc(ptr, old_size, new_size);
	if (!new_ptr && new_size > 0)
		error(game, "ft_realloc() failed");
	return (new_ptr);
}

/**
 * @brief Concatenates two strings and frees both originals.
 *
 * Uses ft_strjoin to concatenate. If allocation fails, both inputs are freed
 * and the error() function is called.
 *
 * @param game Pointer to the game context.
 * @param s1 First string to join and free.
 * @param s2 Second string to join and free.
 * @return Newly allocated concatenated string.
 */
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

/**
 * @brief Duplicates a string with error handling.
 *
 * Wraps ft_strdup and exits if the allocation fails.
 *
 * @param game Pointer to the game context (used in case of error).
 * @param s String to duplicate.
 * @return Pointer to the newly duplicated string.
 */
char	*x_strdup(t_game *game, const char *s)
{
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
		error(game, "ft_strdup() failed");
	return (dup);
}

/**
 * @brief Allocates memory using malloc with error handling.
 *
 * Exits the program using error() if malloc fails.
 *
 * @param game Pointer to the game context (used in case of error).
 * @param size Number of bytes to allocate.
 * @return Pointer to allocated memory.
 */
void	*x_malloc(t_game *game, size_t size)
{
	char	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error(game, "malloc() failed");
	return (ptr);
}
