/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:28 by ykarimi           #+#    #+#             */
/*   Updated: 2025/02/20 18:19:24 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}


bool	is_map_surrounded_by_walls(t_map *map)
{
	size_t	row_index;
	size_t	col_index;

	row_index = 0;
	col_index = 0;
	while (col_index < map->width)
	{
		if (map->grid[0][col_index] != '1')
		{
			printf("First row not surrounded by walls at col_index: %zu, char: %c\n", col_index, map->grid[0][col_index]);
			return (print_error("Map is not surrounded by walls."), false);
		}
		if (map->grid[map->height - 1][col_index] != '1')
		{
			printf("Last row not surrounded by walls at col_index: %zu, char: %c\n", col_index, map->grid[map->height - 1][col_index]);
			return (print_error("Map is not surrounded by walls."), false);
		}
		col_index++;
	}
	while (row_index < map->height)
	{
		if (map->grid[row_index][0] != '1')
		{
			printf("First column not surrounded by walls at row_index: %zu, char: %c\n", row_index, map->grid[row_index][0]);
			return (print_error("Map is not surrounded by walls."), false);
		}
		if (map->grid[row_index][map->width - 1] != '1')
		{
			printf("Last column not surrounded by walls at row_index: %zu, char: %c\n", row_index, map->grid[row_index][map->width - 1]);
			return (print_error("Map is not surrounded by walls."), false);
		}
		row_index++;
	}
	return (true);
}

// bool	validate_map_characters(t_map *map)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	printf("first index of map: %d\n", map->first_index);
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (map->grid[i][j])
// 		{
// 			if (!is_valid_map_char(map->grid[i][j]))
// 			{
// 				printf("map char: %c.\n", map->grid[i][j]);
// 				printf("it's on i: %zu and j: %zu\n", i, j);
// 				printf("Line: %s\n", map->grid[i]);
// 				print_error("Invalid map character.");
// 				return (false);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (true);
// }


bool validate_map_characters(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (map->grid[i])
    {
        j = 0;
        while (map->grid[i][j])
        {
            if (!is_valid_map_char(map->grid[i][j]))
            {
                printf("Invalid map character: %c at line %d, position %d\n", map->grid[i][j], i, j);
                printf("Line: %s\n", map->grid[i]);
                print_error("Invalid map character.");
                return false;
            }
            j++;
        }
        i++;
    }
    return true;
}
// bool validate_map_characters(t_map *map)
// {
//     int i;
//     int j;
// 	int k = 6;
// 	int l = 5;

//     i = map->first_index;
// 	printf("maps first: %d\n", i);
// 	printf("Line before loop: %s\n", map->grid[i]);
// 	printf("6-line is: %s\n", map->grid[k]);
// 	printf("5-line is: %s\n", map->grid[l]);
// 	printf("0-line is: %s\n", map->grid[0]);
//     while (i <= map->last_index)
//     {
//         j = 0;
//         while (map->grid[i][j])
//         {
//             if (!is_valid_map_char(map->grid[i][j]))
//             {
//                 printf("Invalid map character: %c at line %d, position %d\n", map->grid[i][j], i, j);
//                 printf("Line: %s\n", map->grid[i]);
//                 print_error("Invalid map character.");
//                 return false;
//             }
//             j++;
//         }
//         i++;
//     }
//     return true;
// }


bool	is_map_last_in_file(char **lines, t_map *map)
{
	int		i;
	char	*trimmed_line;
	
	i = map->last_index + 1;
	while (lines[i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		if (trimmed_line[0] != '\0' && !is_valid_map_char(trimmed_line[0]))
		{
			print_error("Map is not last in file.");
			free(trimmed_line);
			return (false);
		}
		free(trimmed_line);
		i++;
	}
	return (true);
}
