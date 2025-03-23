/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:36:43 by yasamankari       #+#    #+#             */
/*   Updated: 2025/03/23 11:01:06 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	**create_visited_array(int height, int width)
// {
// 	int **visited;
// 	int	i;
// 	int	j;
// 	j = 0;
// 	i = 0;

// 	visited = malloc(height * sizeof(int *));
// 	if (!visited)
// 		return(NULL);
// 	while (i < height)
// 	{
// 		visited[i] = malloc(width * sizeof(int));
// 		if (!visited[i])
// 		{
// 			while (j < i)
// 			{
// 				free(visited[j]);
// 				j++;
// 			}
// 			free(visited);
// 			return (NULL);
// 		}
// 		j = 0;
// 		while (j < width)
// 		{
// 			visited[i][j] = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (visited);
// }

// static void	free_visited_array(int **visited, int height)
// {
// 	int	i;

// 	i = 0;
// 	while (i < height)
// 	{
// 		free(visited[i]);
// 		i++;
// 	}
// 	free(visited);
// }

// static void	flood_fill(t_map *map, int **visited, size_t x, size_t y)
// {
// 	if (x > 0 && x < map->width - 1 && y > 0 && y < map->height - 1 &&
// 		map->grid[y][x]!= '1' && visited[y][x] == 0)
// 		{
// 			visited[y][x] = 1;
// 			flood_fill(map, visited, x + 1, y);
// 			flood_fill(map, visited, x - 1, y);
// 			flood_fill(map, visited, x, y + 1);
// 			flood_fill(map, visited, x, y - 1);
// 		}
// }

// bool	is_player_entrapped(t_map *map)
// {
// 	int		player_x;
// 	int		player_y;
// 	bool	entrapped;
// 	int		**visited;
// 	size_t		y;
// 	size_t		x;

// 	player_x = map->player->x;
// 	player_y = map->player->y;
// 	y = 1;
// 	x = 1;
// 	visited = create_visited_array(map->height, map->width);
// 	if (!visited)
// 		return (false);
// 	flood_fill(map, visited, player_x, player_y);
// 	entrapped = false;
// 	while(y < map->height - 1 && !entrapped)
// 	{
// 		while (x < map->width - 1 && !entrapped)
// 		{
// 			if (map->grid[y][x] != '1' && visited[y][x] == 0)
// 				entrapped = true;
// 			x++;
// 		}
// 		y++;
// 	}
// 	free_visited_array(visited, map->height);
// 	return (entrapped);
// }


 
// Helper function to check if a move in a direction is possible
static bool can_move_direction(t_map *map, int x, int y, int dx, int dy)
{
    size_t new_x = x + dx;
    size_t new_y = y + dy;

    // Check if the new position is within the map bounds and not a wall
    if (new_x > 0 && new_x < map->width - 1 &&
        new_y > 0 && new_y < map->height - 1 &&
        map->grid[new_y][new_x] != '1')
    {
        return (true); // Can move in this direction
    }
    else
    {
        return (false); // Cannot move in this direction
    }
}


bool is_player_entrapped(t_map *map)
{
    int player_x = map->player->x;
    int player_y = map->player->y;

    // Check if there's space to move in each direction
    if (!can_move_direction(map, player_x, player_y, 0, 1) && // North
        !can_move_direction(map, player_x, player_y, 0, -1) && // South
        !can_move_direction(map, player_x, player_y, 1, 0) && // East
        !can_move_direction(map, player_x, player_y, -1, 0))  // West
    {
        return (true); // Player is entrapped
    }
    else
    {
        return (false); // Player is not entrapped
    }
}
