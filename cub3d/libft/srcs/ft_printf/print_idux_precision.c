/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_idux_precision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:49:29 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:05:49 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*apply_precision_zero_padding(t_pf *pf, char *str, int *len,
															int is_neg)
{
	int		zero_padding;
	char	*new_str;

	if (pf->fmt->precision > *len - is_neg)
	{
		zero_padding = pf->fmt->precision - (*len - is_neg);
		new_str = ft_calloc(pf->fmt->precision + is_neg + 1, sizeof(char));
		if (!new_str)
		{
			pf->malloc_error = 1;
			free(str);
			return (NULL);
		}
		if (is_neg == 1)
			new_str[0] = '-';
		ft_memset(new_str + is_neg, '0', zero_padding);
		ft_strlcpy(new_str + is_neg + zero_padding, str + is_neg,
			(*len - is_neg) + 1);
		*len = pf->fmt->precision + is_neg;
		free(str);
		return (new_str);
	}
	return (str);
}

static char	*handle_hashflag_zero_prec(int *len, char *str, t_pf *pf)
{
	if ((pf->fmt->flags & FLAG_HASH)
		&& (pf->fmt->specifier == 'x' || pf->fmt->specifier == 'X'))
	{
		*len = 1;
		return (str);
	}
	else
	{
		free(str);
		*len = 0;
		str = ft_strdup("");
		if (!str)
		{
			pf->malloc_error = 1;
			return (NULL);
		}
		return (str);
	}
}

char	*handle_precision_int(t_fmt *fmt, char *str, int *len, t_pf *pf)
{
	int	is_negative;

	if (str == NULL || fmt->precision == -1)
		return (str);
	if (fmt->specifier == 'd' || fmt->specifier == 'i')
		is_negative = (str[0] == '-');
	else
		is_negative = 0;
	if (*str == '0' && str[1] == '\0')
	{
		if (fmt->precision == 0)
		{
			str = handle_hashflag_zero_prec(len, str, pf);
			if (!str)
				return (NULL);
		}
	}
	str = apply_precision_zero_padding(pf, str, len, is_negative);
	if (!str)
		return (NULL);
	return (str);
}
