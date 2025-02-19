/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:19:58 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:12:36 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_pf	*pf;
	int		total;
	int		error;

	error = 0;
	if (format == NULL)
		return (-1);
	pf = (t_pf *)malloc(sizeof(t_pf));
	if (pf == NULL)
		return (-1);
	if (initialize_printf_structs(pf) == -1)
		return (-1);
	va_start(args, format);
	process_format_string(format, &args, pf);
	va_end(args);
	total = pf->total;
	if (pf->malloc_error == 1 || pf->write_error == 1)
		error = -1;
	free(pf->fmt);
	free(pf);
	if (error == -1)
		return (error);
	else
		return (total);
}
