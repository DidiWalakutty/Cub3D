/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:42:53 by ykarimi           #+#    #+#             */
/*   Updated: 2025/02/20 18:16:50 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_spawning_point(t_map *map, t_player *player)
{
	int	row_index;
	int	col_index;
	int	player_count;

	row_index = 0;
	player_count = 0;
	while (map->grid[row_index])
	{
		col_index = 0;
		while (map->grid[row_index][col_index])
		{
			if (ft_strchr("NSEW", map->grid[row_index][col_index]))
			{
				player->x = col_index;
				player->y = row_index;
				player->orientation = map->grid[row_index][col_index];
				player_count++;
			}
			col_index++;
		}
		row_index++;
	}
	player->player_count = player_count;
}

int	check_player_spawning_point(t_player *player)
{
	if (player->player_count != 1)
	{
		if (player->player_count  == 0)
			print_error("No player.");
		else
			print_error("Multiple players.");
		return (1);
	}
	return (0);
}
