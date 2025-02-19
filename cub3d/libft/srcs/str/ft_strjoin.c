/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:45:28 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/18 23:43:04 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	new_str = (char *)malloc((total_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcpy(new_str + s1_len, s2, s2_len + 1);
	return (new_str);
}

/**
 * ft_strjoin_and_free - Joins two strings and frees the specified one(s).
 *
 * @s1: First string to join.
 * @s2: Second string to join.
 * @free_s1: If true (1), frees `s1` after joining.
 * @free_s2: If true (1), frees `s2` after joining.
 *
 * Returns:
 * - A newly allocated string (s1 + s2).
 * - NULL if allocation fails.
 *
 * Usage:
 * ```c
 * char *s1 = ft_strdup("Hello");
 * char *s2 = ft_strdup(" World!");
 * char *result = ft_strjoin_and_free(s1, s2, 1, 1);  // Joins and frees both
 * ```
 */
char	*ft_strjoin_and_free(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcpy(new_str + s1_len, s2, s2_len + 1);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (new_str);
}
