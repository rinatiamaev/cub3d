/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_memory_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:57:43 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/26 20:58:08 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**x_copy_strarray(t_game *game, char **array)
{
	char	**copy;

	copy = ft_copy_strarray(array);
	if (!copy)
		error(game, "ft_copy_strarray() failed");
	return (copy);
}
