/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:13:08 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/16 14:55:22 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void	skip_whitespace_index(const char *input, int *i)
{
	while (ft_isspace(input[*i]))
		(*i)++;
}

char	*skip_whitespace_ptr(const char *s)
{
	while (ft_isspace(*s))
		s++;
	return ((char *)s);
}
