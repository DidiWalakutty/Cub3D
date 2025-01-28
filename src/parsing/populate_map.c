/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:58 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/28 15:44:51 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	get_map_dimensions(t_map *map)
{
	int	height;
	int	width;
	int	i;
	int	line_len;
	
	line_len = 0;
	height = 0;
	width = 0;
	i = 0;
	while(map->grid[i])
	{
		line_len = ft_strlen(map->grid[i]);
		if (line_len > width)
			width = line_len;
		height++;
		i++;
	}
	map->width = width;
	map->height = height;
	//printf("map width: %d, and map height: %d\n", width, height);
}

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

/* access to  player struct is convoluted, needs to be changed */
int	populate_map(t_input *file_data)
{
	t_player	*player;

	get_map_dimensions(file_data->map); // get hight and width of the map - what else?
	player = malloc(sizeof(t_player));
	if (!player)
		return (1);
	file_data->map->player = player;
	ft_bzero(player, sizeof(t_player));
	set_player_spawning_point(file_data->map, player); //position and orientation
	if (check_player_spawning_point(player) == 1)
		return (1);
	printf("@@@@@@@@@@\n");
	print_map(file_data->map->grid);
	return (0);
}