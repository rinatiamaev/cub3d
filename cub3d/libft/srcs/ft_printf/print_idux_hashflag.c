/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_idux_hashflag.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:15:56 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:05:45 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	requires_alternative_form(char specifier, char *str)
{
	if (str == NULL || str[0] == '\0' || ft_strcmp(str, "0") == 0)
		return (0);
	if (specifier == 'x' || specifier == 'X')
		return (1);
	return (0);
}

char	*prepend_alternative_form(char *str, char specifier, t_pf *pf)
{
	int		len;
	char	*new_str;

	if (!str || str[0] == '\0' || ft_strcmp(str, "0") == 0)
		return (str);
	if (specifier != 'x' && specifier != 'X')
		return (str);
	len = ft_strlen(str);
	new_str = (char *)malloc(len + 3);
	if (!new_str)
	{
		pf->malloc_error = 1;
		free(str);
		return (NULL);
	}
	new_str[0] = '0';
	new_str[1] = specifier;
	ft_strlcpy(new_str + 2, str, len + 1);
	free(str);
	return (new_str);
}

int	get_alternative_form_length(char specifier)
{
	if (specifier == 'x' || specifier == 'X')
		return (2);
	return (0);
}
