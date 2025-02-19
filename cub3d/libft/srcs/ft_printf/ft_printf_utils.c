/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:05:48 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:12:21 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	initialize_pf(t_pf *pf)
{
	pf->total = 0;
	pf->write_error = 0;
	pf->malloc_error = 0;
}

static void	initialize_fmt(t_fmt *fmt)
{
	fmt->flags = 0;
	fmt->width = 0;
	fmt->precision = -1;
	fmt->specifier = 0;
}

int	initialize_printf_structs(t_pf *pf)
{
	initialize_pf(pf);
	pf->fmt = (t_fmt *)malloc(sizeof(t_fmt));
	if (pf->fmt == NULL)
		return (-1);
	initialize_fmt(pf->fmt);
	return (0);
}

int	is_valid_flag(char c)
{
	return (c == '#' || c == '0' || c == '-' || c == '+' || c == ' ');
}
