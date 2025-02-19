/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_csper_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:03:25 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:05:37 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_padding(int padding, char pad_char, t_pf *pf)
{
	if (padding <= 0)
		return ;
	while (padding > 0)
	{
		write_char_safely(1, pad_char, pf);
		if (pf->write_error != 0)
			return ;
		padding--;
	}
}

int	handle_precision_s(t_fmt *fmt, int len)
{
	if (fmt->precision >= 0 && fmt->precision < len)
		len = fmt->precision;
	return (len);
}

int	handle_width(t_fmt *fmt, size_t len)
{
	int	padding;

	padding = fmt->width - len;
	if (padding < 0)
		padding = 0;
	return (padding);
}
