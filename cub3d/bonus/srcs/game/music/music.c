/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riamaev <riamaev@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:18:42 by riamaev           #+#    #+#             */
/*   Updated: 2025/03/09 20:19:23 by riamaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	start_background_music(const char *music_file)
{
	char	command[256];

	ft_strcpy(command, "aplay ");
	ft_strcat(command, music_file);
	ft_strcat(command, " &");
	system(command);
}

void	stop_background_music()
{
	system("pkill aplay");
}
