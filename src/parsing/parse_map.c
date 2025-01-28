/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:48 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/28 18:02:57 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"



// static void get_map_properties(char **lines, t_map *map)
// {
//     int i;
//     int height = 0;
//     int width = 0;

//     //map->first_index = map_start_index;
//     i = map_start_index;
//     while (lines[i])
//     {
//         if (lines[i][0] != '\0' && is_valid_map_char(lines[i][0]))
//         {
//             map->last_index = i;
//             height++;
//             int line_length = ft_strlen(lines[i]);
//             if (line_length > width)
//                 width = line_length;
//         }
//         i++;
//     }
//     //map->height = height;
//     //map->width = width;
//     //printf("first index: %d, last index: %d\n", map->first_index, map->last_index);
//     //printf("first index line: %s\n", lines[map->first_index]);
//     //printf("last index line: %s\n", lines[map->last_index]);
//     //printf("map width: %d, and map height: %d\n", width, height);
// }


/*
might need to improve logic
*/
// bool	is_map_last_in_file(char **lines, int map_start_index)
// {
// 	int	i;

// 	i = map_start_index;
// 	while (lines[i])
// 	{
// 		if (lines[i][0] != '\0' && !is_valid_map_char(lines[i][0]))
// 		{
// 			printf("illigal map content found.");
// 			return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }


// bool	parse_map(char **lines, t_input *content, int map_start_index)
// {
// 	int	i;
// 	int	j;

// 	i = map_start_index;
// 	while (lines[i])
// 	{
// 		j = 0;
// 		while (lines[i][j])
// 		{
// 			if (!is_valid_map_char(lines[i][j]))
// 			{
// 				print_error("Invalid map character.");
// 				return (false);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	get_map_properties(lines, content->map, map_start_index); // get map first and last index, height and width,and update the struct, malloc for grid.
// 	if (!is_map_last_in_file(lines, map_start_index)) // use the updated indices from the struct to determine if map is last in file
// 		return (false);
// 	return (true);
// }


// static bool populate_grid(char **lines, t_map *map)
// {
//     for (int i = 0; i < map->height; i++)
//     {
//         map->grid[i] = ft_strdup(lines[map->first_index + i]);
//         if (!map->grid[i])
//         {
//             // Free previously allocated memory if allocation fails
//             while (--i >= 0)
//                 free(map->grid[i]);
//             free(map->grid);
//             print_error("Memory allocation for map row failed.");
//             return false;
//         }
//     }
//     map->grid[map->height] = NULL;
//     return true;
// }

// static bool validate_map_characters(t_map *map)
// {
//     for (int i = 0; i < map->height; i++)
//     {
//         for (int j = 0; map->grid[i][j]; j++)
//         {
//             if (!is_valid_map_char(map->grid[i][j]))
//             {
//                 print_error("Invalid map character.");
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// bool parse_map(char **lines, t_input *content)
// {
//     // Get map properties: height, width, first and last indices
//     get_map_properties(lines, content->map);

//     // Check if the map is the last part of the file
//     if (!is_map_last_in_file(lines, content->map))
//         return false;

//     // Allocate memory for the grid and populate it
//     content->map->grid = malloc(sizeof(char *) * (content->map->height + 1));
//     if (!content->map->grid)
//     {
//         print_error("Memory allocation for map grid failed.");
//         return false;
//     }

//     if (!populate_grid(lines, content->map))
//         return false;

//     // Validate map characters
//     if (!validate_map_characters(content->map))
//         return false;

//     // Check if the map is surrounded by walls
//     if (!is_map_surrounded_by_walls(content->map->grid))
//         return false;

//     return true;
// }