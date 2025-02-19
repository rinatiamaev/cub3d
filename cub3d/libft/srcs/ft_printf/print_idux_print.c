/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_idux_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 07:49:55 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:05:52 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*prepend_sign(char *str, char sign, t_pf *pf)
{
	int		len;
	char	*new_str;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (new_str == NULL)
	{
		pf->malloc_error = 1;
		free(str);
		return (NULL);
	}
	new_str[0] = sign;
	ft_strlcpy(new_str + 1, str, len + 1);
	free(str);
	return (new_str);
}

static char	*apply_plus_space_hash_flags(t_pf *pf, char *str, int *len)
{
	if ((pf->fmt->specifier == 'd' || pf->fmt->specifier == 'i')
		&& (pf->fmt->flags & FLAG_PLUS) && ft_isstrpositive(str))
	{
		str = prepend_sign(str, '+', pf);
		if (str == NULL)
			return (NULL);
		(*len)++;
	}
	else if ((pf->fmt->specifier == 'd' || pf->fmt->specifier == 'i')
		&& (pf->fmt->flags & FLAG_SPACE) && ft_isstrpositive(str))
	{
		str = prepend_sign(str, ' ', pf);
		if (str == NULL)
			return (NULL);
		(*len)++;
	}
	if ((pf->fmt->flags & FLAG_HASH)
		&& requires_alternative_form(pf->fmt->specifier, str))
	{
		str = prepend_alternative_form(str, pf->fmt->specifier, pf);
		if (str == NULL)
			return (NULL);
		*len += get_alternative_form_length(pf->fmt->specifier);
	}
	return (str);
}

static void	print_with_padding(t_pf *pf, char *str, int padding)
{
	if (!(pf->fmt->flags & FLAG_MINUS) && !(pf->fmt->flags & FLAG_ZERO))
	{
		print_padding(padding, ' ', pf);
		if (pf->write_error != 0)
			return ;
	}
	write_safely(1, str, pf);
	if (pf->write_error != 0)
		return ;
	if (pf->fmt->flags & FLAG_MINUS)
	{
		print_padding(padding, ' ', pf);
		if (pf->write_error != 0)
			return ;
	}
}

static void	print_zero_padding_int(int padding, char **str_ptr, t_pf *pf)
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

void	print_formatted_number(t_fmt *fmt, char *str, int len, t_pf *pf)
{
	int		padding;
	char	*formatted_str;
	char	*temp_ptr;

	formatted_str = apply_plus_space_hash_flags(pf, str, &len);
	if (formatted_str == NULL)
		return ;
	padding = handle_width(fmt, len);
	temp_ptr = formatted_str;
	if ((fmt->flags & FLAG_ZERO) && !(fmt->flags & FLAG_MINUS)
		&& fmt->precision < 0)
	{
		print_zero_padding_int(padding, &temp_ptr, pf);
		if (pf->write_error != 0)
			return ;
		write_safely(1, temp_ptr, pf);
		if (pf->write_error != 0)
			return ;
	}
	else
		print_with_padding(pf, formatted_str, padding);
	if (pf->write_error != 0)
		return ;
	free(formatted_str);
}
