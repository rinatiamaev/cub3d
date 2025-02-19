/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toonsa <toonsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:43:12 by nlouis            #+#    #+#             */
/*   Updated: 2024/11/24 02:45:26 by toonsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	bytes_written;
	int	total_written;
	int	len;

	if (str == NULL)
		return (-1);
	total_written = 0;
	len = ft_strlen(str);
	while (total_written < len)
	{
		bytes_written = write(fd, str + total_written, len - total_written);
		if (bytes_written == -1)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		total_written += bytes_written;
	}
	return (total_written);
}
