/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 07:16:11 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:06:07 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	parse_and_handle_specifier(t_fmt *fmt, va_list *args, t_pf *pf)
{
	if (fmt->specifier == 'c')
		format_and_print_c(fmt, args, pf);
	else if (fmt->specifier == 's')
		format_and_print_s(fmt, args, pf);
	else if (fmt->specifier == 'i' || fmt->specifier == 'd')
		format_and_print_id(fmt, args, pf);
	else if (fmt->specifier == 'u')
		format_and_print_u(fmt, args, pf);
	else if (fmt->specifier == 'x')
		format_and_print_x(fmt, args, 0, pf);
	else if (fmt->specifier == 'X')
		format_and_print_x(fmt, args, 1, pf);
	else if (fmt->specifier == '%')
		format_and_print_percent(fmt, pf);
	if (pf->write_error != 0 || pf->malloc_error != 0)
		return ;
}

static void	reset_fmt(t_fmt *fmt)
{
	fmt->flags = 0;
	fmt->width = 0;
	fmt->precision = -1;
	fmt->specifier = '\0';
}

static void	process_conv_spec(const char **format, va_list *args, t_pf *pf)
{
	const char	*start_format;

	reset_fmt(pf->fmt);
	start_format = *format - 1;
	if (setup_format(format, pf->fmt) == -1)
	{
		while (start_format < *format)
		{
			write_char_safely(1, *start_format, pf);
			if (pf->write_error != 0)
				return ;
			start_format++;
		}
		return ;
	}
	parse_and_handle_specifier(pf->fmt, args, pf);
	if (pf->write_error != 0 || pf->malloc_error != 0)
		return ;
}

void	process_format_string(const char *format, va_list *args, t_pf *pf)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return ;
			process_conv_spec(&format, args, pf);
			if (pf->write_error != 0 || pf->malloc_error != 0)
				return ;
		}
		else
		{
			write_char_safely(1, *format, pf);
			if (pf->write_error != 0)
				return ;
			format++;
		}
	}
}
