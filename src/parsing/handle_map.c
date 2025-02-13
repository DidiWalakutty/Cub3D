/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:12 by ykarimi           #+#    #+#             */
/*   Updated: 2025/02/13 16:54:39 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static bool populate_grid(char **lines, t_map *map)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < map->height)
// 	{
// 		map->grid[i] = ft_strdup(lines[map->first_index + i]);
// 		if (!map->grid[i])
// 		{
// 			while (--i >= 0)
// 				free(map->grid[i]);
// 			free(map->grid);
// 			return (false);
// 		}
// 		i++;
// 	}
// 	map->grid[map->height] = NULL;
// 	return (true);
// }



// bool populate_grid(char **lines, t_map *map)
// {
//     int i;
//     int j;
//     char *trimmed_line;

//     i = map->first_index;
//     j = 0;
//     //printf("Populating grid from first_index: %d to last_index: %d\n", map->first_index, map->last_index);
//     while (i <= map->last_index)
//     {
//         trimmed_line = ft_strtrim(lines[i], " \t\n\r");
//         if (trimmed_line[0] != '\0') // Skip empty lines
//         {
//             printf("Copying line %d: %s\n", i, trimmed_line);
//             map->grid[j] = ft_strdup(trimmed_line);
//             free(trimmed_line);
//             if (!map->grid[j])
//             {
//                 print_error("Memory allocation for map grid line failed.");
//                 return false;
//             }
//             j++;
//         }
//         else
//         {
//             free(trimmed_line);
//         }
//         i++;
//     }
//     map->grid[j] = NULL;
//     //printf("Finished populating grid.\n");
//     return true;
// }

bool populate_grid(char **lines, t_map *map)
{
    int i;
    int j;

    i = map->first_index;
    j = 0;
    //printf("Populating grid from first_index: %d to last_index: %d\n", map->first_index, map->last_index);
    while (i <= map->last_index)
    {
        //printf("Copying line %d: %s\n", i, lines[i]);
        map->grid[j] = ft_strdup(lines[i]);
        if (!map->grid[j])
        {
            print_error("Memory allocation for map grid line failed.");
            return false;
        }
        i++;
        j++;
    }
    map->grid[j] = NULL;
    //printf("Finished populating grid.\n");
    return true;
}

static int	skip_non_map_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && (ft_strncmp(lines[i], "NO ", 3) == 0 || \
						ft_strncmp(lines[i], "SO ", 3) == 0 || \
						ft_strncmp(lines[i], "WE ", 3) == 0 || \
						ft_strncmp(lines[i], "EA ", 3) == 0 || \
						ft_strncmp(lines[i], "F ", 2) == 0 || \
						ft_strncmp(lines[i], "C ", 2) == 0 || \
						lines[i][0] == '\0' || ft_isspace(lines[i][0])))
		i++;
	return (i);
}

static void get_map_properties(char **lines, t_map *map)
{
    int height;
    int width;
    int i;
    int line_len;
    char *trimmed_line;

    height = 0;
    width = 0;
    i = skip_non_map_lines(lines);
    map->first_index = i;
    while (lines[i])
    {
        trimmed_line = ft_strtrim(lines[i], " \t\n\r");
        if (trimmed_line[0] != '\0' && is_valid_map_char(trimmed_line[0]))
        {
            line_len = ft_strlen(trimmed_line);
            if (line_len > width)
                width = line_len;
            height++;
            map->last_index = i; // Update last_index only for non-empty lines
        }
        free(trimmed_line);
        i++;
    }
    map->height = height;
    map->width = width;
    //printf("first index: %d, last index: %d\n", map->first_index, map->last_index);
    //printf("first index line: %s\n", lines[map->first_index]);
    //printf("last index line: %s\n", lines[map->last_index]);
   //printf("map width: %d, and map height: %d\n", width, height);
}


// static void	get_map_properties(char **lines, t_map *map)
// {
// 	int height;
// 	int width;
// 	int i;
// 	int line_len;

// 	height = 0;
// 	width = 0;
// 	i = 0;
// 	line_len = 0;
// 	// trim empty spaces from end of lines
// 	i = skip_non_map_lines(lines);
// 	map->first_index = i;
// 	while (lines[i])
// 	{
// 		if (is_valid_map_char(lines[i][0]))
// 		{
// 			//map->last_index = i;
// 			//height++;
// 			line_len = ft_strlen(lines[i]);
// 			if (line_len > width)
// 				width = line_len;
// 			height++;
// 			map->last_index = i;
// 		}
// 		i++;
// 	}
// 	map->height = height;
// 	map->width = width;
// 	printf("first index: %d, last index: %d\n", map->first_index, map->last_index);
// 	printf("first index line: %s\n", lines[map->first_index]);
// 	printf("last index line: %s\n", lines[map->last_index]);
// 	printf("map width: %d, and map height: %d\n", width, height);
// }


static int	init_map(t_input *file_data)
{
	file_data->map = malloc(sizeof(t_map));
	if (!file_data->map)
	{
		print_error("map initialization failed.");
		return (1);
	}
	ft_bzero(file_data->map, sizeof(t_map));
	return (0);
}

bool	handle_map(t_input *file_data, char **lines)
{
	t_player	*player;

	if (init_map(file_data) == 1)
		return (false);
	get_map_properties(lines, file_data->map);
	if (!is_map_last_in_file(lines, file_data->map))
		return (false);
	file_data->map->grid = malloc(sizeof(char *) * (file_data->map->height + 1));
	if (!file_data->map->grid)
	{
		print_error("Memory allocation for map grid failed.");
		return (false);
	}
	if (!populate_grid(lines, file_data->map))
		return (false);
	//print_map(file_data->map->grid);
	if (!validate_map_characters(file_data->map))
		return (false);
	// print_map(file_data->map->grid);
	if (!is_map_surrounded_by_walls(file_data->map))
		return (false);
	player = malloc(sizeof(t_player));
	if (!player)
		return (false);
	file_data->map->player = player;
	ft_bzero(player, sizeof(t_player));
	set_player_spawning_point(file_data->map, player); //position and orientation
	if (check_player_spawning_point(player) == 1)
		return (false);
	return (true);
}
