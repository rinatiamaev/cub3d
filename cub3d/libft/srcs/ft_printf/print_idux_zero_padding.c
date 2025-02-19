/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_idux_zero_padding.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:26:52 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:05:55 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_zero_padding_int(int padding, char **str_ptr, t_pf *pf)
{
	int		sign;
	char	pad_char;

	pad_char = '0';
	sign = ((*str_ptr)[0] == '-' || (*str_ptr)[0] == '+'
			|| (*str_ptr)[0] == ' ');
	if (padding <= 0)
		return ;
	if (pad_char == '0' && sign == 1)
	{
		write_char_safely(1, (*str_ptr)[0], pf);
		if (pf->write_error != 0)
			return ;
		*str_ptr += 1;
	}
	while (padding > 0)
	{
		write_char_safely(1, pad_char, pf);
		if (pf->write_error != 0)
			return ;
		padding--;
	}
}
