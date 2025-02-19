/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:28:23 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:06:10 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	parse_flags(const char **format, t_fmt *fmt)
{
	while (**format && is_valid_flag(**format))
	{
		if (**format == '#')
			fmt->flags |= FLAG_HASH;
		else if (**format == '0')
			fmt->flags |= FLAG_ZERO;
		else if (**format == '-')
			fmt->flags |= FLAG_MINUS;
		else if (**format == '+')
			fmt->flags |= FLAG_PLUS;
		else if (**format == ' ')
			fmt->flags |= FLAG_SPACE;
		(*format)++;
	}
}

static void	parse_width(const char **format, t_fmt *fmt)
{
	fmt->width = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
}

static void	parse_precision(const char **format, t_fmt *fmt)
{
	if (**format == '.')
	{
		(*format)++;
		if (ft_isdigit(**format))
		{
			fmt->precision = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
		else
			fmt->precision = 0;
	}
}

static int	parse_specifier(const char **format, t_fmt *fmt)
{
	if (**format == '\0')
		return (-1);
	if (ft_strchr("cspdiuxX%", **format))
	{
		fmt->specifier = **format;
		(*format)++;
		return (0);
	}
	fmt->specifier = '\0';
	return (-1);
}

int	setup_format(const char **format, t_fmt *fmt)
{
	parse_flags(format, fmt);
	parse_width(format, fmt);
	parse_precision(format, fmt);
	if (parse_specifier(format, fmt) == -1)
		return (-1);
	return (0);
}
