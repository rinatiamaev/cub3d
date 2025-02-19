/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:33:58 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 14:26:24 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_split()
 * Splits a string into an array of substrings using a delimiter.
 *
 * @s: The input string to split.
 * @c: The delimiter character.
 *
 * Returns: A dynamically allocated NULL-terminated array of substrings,
 * or NULL on failure.
 *
 * Usage:
 * - Use `ft_split()` to separate words in a string based on a delimiter.
 * - It handles multiple consecutive delimiters correctly.
 * - Each word is allocated separately, and the array should be freed with
 * `ft_free_array()`.
 */

static size_t	ft_w_count(const char *str, char c)
{
	size_t	w_count;
	int		in_word;

	w_count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && in_word == 0)
		{
			w_count++;
			in_word = 1;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (w_count);
}

static int	ft_fill_array(char **array, const char *s, char c, size_t w_count)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (i < w_count)
	{
		while (*s == c)
			s++;
		word_len = 0;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		array[i] = ft_substr(s, 0, word_len);
		if (!array[i])
		{
			ft_free_array((void **)array);
			return (0);
		}
		s += word_len;
		i++;
	}
	array[i] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char		**array;
	size_t		w_count;

	if (!s)
		return (NULL);
	w_count = ft_w_count(s, c);
	array = (char **)ft_calloc(w_count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	if (!ft_fill_array(array, s, c, w_count))
	{
		free(array);
		return (NULL);
	}
	return (array);
}
