/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_csper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:08:57 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/16 22:40:16 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	format_and_print_percent(t_fmt *fmt, t_pf *pf)
{
	int		padding;
	char	pad_char;

	if (fmt->flags & FLAG_ZERO)
		pad_char = '0';
	else
		pad_char = ' ';
	padding = handle_width(fmt, 1);
	if (!(fmt->flags & FLAG_MINUS))
	{
		print_padding(padding, pad_char, pf);
		if (pf->write_error != 0)
			return ;
	}
	write_char_safely(1, '%', pf);
	if (pf->write_error != 0)
		return ;
	if (fmt->flags & FLAG_MINUS)
	{
		print_padding(padding, ' ', pf);
		if (pf->write_error != 0)
			return ;
	}
}

void	format_and_print_c(t_fmt *fmt, va_list *args, t_pf *pf)
{
	char	c;
	int		padding;

	c = va_arg(*args, int);
	padding = handle_width(fmt, 1);
	if (!(fmt->flags & FLAG_MINUS))
	{
		print_padding(padding, ' ', pf);
		if (pf->write_error != 0)
			return ;
	}
	write_char_safely(1, c, pf);
	if (pf->write_error != 0)
		return ;
	if (fmt->flags & FLAG_MINUS)
	{
		print_padding(padding, ' ', pf);
		if (pf->write_error != 0)
			return ;
	}
}

void	format_and_print_s(t_fmt *fmt, va_list *args, t_pf *pf)
{
	char	*str;
	size_t	len;
	int		padding;

	str = va_arg(*args, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	len = handle_precision_s(fmt, len);
	padding = handle_width(fmt, len);
	if (!(fmt->flags & FLAG_MINUS))
	{
		print_padding(padding, ' ', pf);
		if (pf->write_error != 0)
			return ;
	}
	write_safely_len(1, str, len, pf);
	if (pf->write_error != 0)
		return ;
	if (fmt->flags & FLAG_MINUS)
	{
		print_padding(padding, ' ', pf);
		if (pf->write_error != 0)
			return ;
	}
}
