/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:49:29 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:06:00 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*apply_precision_zero_padding_p(t_fmt *fmt, char *str, int *len,
																	t_pf *pf)
{
	int		zero_padding;
	int		origin_len;
	char	*new_str;

	origin_len = *len;
	if (fmt->precision > origin_len - 2)
		zero_padding = fmt->precision - (origin_len - 2);
	else
		zero_padding = 0;
	*len = origin_len + zero_padding;
	new_str = malloc(*len + 1);
	if (!new_str)
	{
		pf->malloc_error = 1;
		return (NULL);
	}
	new_str[0] = '0';
	new_str[1] = 'x';
	ft_memset(new_str + 2, '0', zero_padding);
	ft_strlcpy(new_str + 2 + zero_padding, str + 2, origin_len - 1);
	return (new_str);
}

char	*handle_precision_p(t_fmt *fmt, char *str, int *len, t_pf *pf)
{
	char	*new_str;

	if (fmt->precision == -1)
		return (str);
	new_str = apply_precision_zero_padding_p(fmt, str, len, pf);
	if (new_str == NULL)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (new_str);
}

void	handle_space_flag_p(t_pf *pf, int *padding)
{
	if (pf->fmt->flags & FLAG_SPACE)
	{
		(*padding)--;
		write_char_safely(1, ' ', pf);
		if (pf->write_error != 0)
			return ;
	}
}

void	handle_minus_flag_p(char *str, int padding, t_pf *pf)
{
	if (pf->fmt->flags & FLAG_MINUS)
	{
		write_safely(1, str, pf);
		if (pf->write_error != 0)
			return ;
		while (padding-- > 0)
		{
			write_char_safely(1, ' ', pf);
			if (pf->write_error != 0)
				return ;
		}
	}
}

void	print_right_aligned_p(t_fmt *fmt, char *str, int padding, t_pf *pf)
{
	char	pad_char;

	if (!(fmt->flags & FLAG_MINUS))
	{
		pad_char = ' ';
		if ((fmt->flags & FLAG_ZERO) && fmt->precision == -1)
			pad_char = '0';
		while (padding-- > 0)
		{
			write_char_safely(1, pad_char, pf);
			if (pf->write_error != 0)
				return ;
		}
		write_safely(1, str, pf);
	}
}
