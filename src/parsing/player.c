/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 12:42:53 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/29 12:43:47 by ykarimi       ########   odam.nl         */
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
				//map->grid[row_index][col_index] = '0'; // Replace player position with empty space
				//printf("p count: %d\n", player_count);
				player_count++;
				//return ;
			}
			col_index++;
		}
		row_index++;
	}
	player->player_count = player_count;
	//printf("player orientation: %c\n", player->orientation);
	//printf("player count from inside first spawn func: %d\n", player_count);
	//printf("player x pos: %d, player y: %d\n", player->x, player->y);
}

int	check_player_spawning_point(t_player *player)
{
	//printf("player count: %d\n", player->player_count);
	if (player->player_count != 1)
	{
		if (player->player_count  == 0)
			printf("No player\n");
		else
			printf("Multiple players\n");
		return (1);
	}
	return (0);
}