/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_safely.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:35:58 by nlouis            #+#    #+#             */
/*   Updated: 2024/12/02 12:06:14 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_safely(int fd, char *str, t_pf *pf)
{
	ssize_t	bytes_written;
	size_t	total_written;
	size_t	len;

	if (str == NULL)
		return ;
	total_written = 0;
	len = ft_strlen(str);
	while (total_written < len)
	{
		bytes_written = write(fd, str + total_written, len - total_written);
		if (bytes_written == -1)
		{
			if (errno == EINTR)
				continue ;
			pf->write_error = 1;
			return ;
		}
		total_written += bytes_written;
	}
	pf->total += total_written;
}

void	write_safely_len(int fd, char *str, size_t len, t_pf *pf)
{
	ssize_t	bytes_written;
	size_t	total_written;

	if (str == NULL)
		return ;
	total_written = 0;
	while (total_written < len)
	{
		bytes_written = write(fd, str + total_written, len - total_written);
		if (bytes_written == -1)
		{
			if (errno == EINTR)
				continue ;
			pf->write_error = 1;
			return ;
		}
		total_written += bytes_written;
	}
	pf->total += total_written;
}

void	write_char_safely(int fd, char c, t_pf *pf)
{
	ssize_t	bytes_written;

	bytes_written = write(fd, &c, 1);
	if (bytes_written == -1)
	{
		if (errno == EINTR)
		{
			write_char_safely(fd, c, pf);
			return ;
		}
		pf->write_error = 1;
		return ;
	}
	pf->total += bytes_written;
}
