/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_with_item.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:48:46 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/24 20:36:16 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_item	*find_closest_item(t_game *game, double range)
{
	t_item	*closest_item;
	double	min_distance;
	double	current_distance;
	int		i;

	closest_item = NULL;
	min_distance = range;
	i = 0;
	while (i < game->item_count)
	{
		current_distance
			= ft_euclidean_dist_dpoint(game->player.pos, game->items[i]->pos);
		if (current_distance <= min_distance
			&& is_facing_target(&game->player, game->items[i]->pos))
		{
			min_distance = current_distance;
			closest_item = game->items[i];
		}
		i++;
	}
	return (closest_item);
}

static void	handle_single_item_removal(t_game *game, t_item *item_to_remove)
{
	free_single_item(game, item_to_remove);
	free(game->items);
	game->items = NULL;
	game->item_count = 0;
}

static t_item	**create_new_item_list(t_game *game, t_item *item_to_remove)
{
	t_item	**new_list;
	int		i;
	int		j;

	new_list = x_calloc(game, game->item_count - 1, sizeof(t_item *));
	i = 0;
	j = 0;
	while (i < game->item_count)
	{
		if (game->items[i] != item_to_remove)
		{
			new_list[j] = game->items[i];
			j++;
		}
		else
			free_single_item(game, game->items[i]);
		i++;
	}
	return (new_list);
}

static void	remove_item_from_list(t_game *game, t_item *item_to_remove)
{
	t_item	**new_list;

	if (game->item_count <= 1)
	{
		handle_single_item_removal(game, item_to_remove);
		return ;
	}
	new_list = create_new_item_list(game, item_to_remove);
	free(game->items);
	game->items = new_list;
	game->item_count--;
}

bool	interact_with_item(t_game *game)
{
	t_item	*item;

	item = find_closest_item(game, 1.5);
	if (!item)
		return (false);
	if (item->is_collectible && !item->is_collected)
	{
		item->is_collected = true;
		if (ft_strcmp(item->name, "bucket") == 0)
			game->player.has_bucket = true;
		if (ft_strcmp(item->name, "key") == 0)
			game->player.has_key = true;
		remove_item_from_list(game, item);
		return (true);
	}
	else if (ft_strcmp(item->name, "well") == 0
		&& game->player.has_bucket && !game->player.has_water)
	{
		show_temp_message(game, 3.0, "You filled up your bucket!");
		game->player.has_water = true;
	}
	return (true);
}
