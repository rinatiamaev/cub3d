/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:38:15 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 15:26:32 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_split_charset
 * Splits a string into an array of substrings using multiple delimiters.
 * Preserves empty fields ("" when consecutive delimiters appear).
 *
 * @s: The input string to split.
 * @charset: A string containing multiple delimiter characters.
 *
 * Returns: A newly allocated NULL-terminated array of substrings, or
 * NULL on failure.
 */
static int	ft_is_charset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static size_t	ft_w_count_charset(char *str, char *charset)
{
	size_t	count;
	int		in_field;

	count = 0;
	in_field = 1;
	while (*str)
	{
		if (ft_is_charset(*str, charset))
		{
			count++;
			in_field = 1;
		}
		else if (in_field)
		{
			in_field = 0;
		}
		str++;
	}
	return (count + 1);
}

static int	ft_fill_array_charset(char **array, char *s,
										char *charset, size_t field_count)
{
	size_t	i;
	size_t	field_len;

	i = 0;
	while (i < field_count)
	{
		field_len = 0;
		while (s[field_len] && !ft_is_charset(s[field_len], charset))
			field_len++;
		array[i] = ft_substr(s, 0, field_len);
		if (!array[i])
		{
			ft_free_array((void **)array);
			return (0);
		}
		s += field_len;
		if (*s)
			s++;
		i++;
	}
	array[i] = NULL;
	return (1);
}

char	**ft_split_charset(char *s, char *charset)
{
	char		**array;
	size_t		field_count;

	if (!s || !charset)
		return (NULL);
	field_count = ft_w_count_charset(s, charset);
	array = (char **)ft_calloc(field_count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	if (!ft_fill_array_charset(array, s, charset, field_count))
	{
		free(array);
		return (NULL);
	}
	return (array);
}
