/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 17:01:12 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/28 18:05:49 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static bool populate_grid(char **lines, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		map->grid[i] = ft_strdup(lines[map->first_index + i]);
		if (!map->grid[i])
        {
            while (--i >= 0)
                free(map->grid[i]);
            free(map->grid);
            print_error("Memory allocation for map row failed.");
            return (false);
        }
		i++;
    }
	map->grid[map->height] = NULL;
    return (true);
}



static void get_map_properties(char **lines, t_map *map)
{
	int	height;
	int	width;
	int	i;
	int	line_len;
	
	line_len = 0;
	height = 0;
	width = 0;
	i = 0;
	while (lines[i] && (lines[i][0] == '\0' || !is_valid_map_char(lines[i][0])))
        i++;
    map->first_index = i;
    while (lines[i])
    {
        if (lines[i][0] != '\0' && is_valid_map_char(lines[i][0]))
        {
            map->last_index = i;
            height++;
            line_len = ft_strlen(lines[i]);
            if (line_len > width)
                width = line_len;
        }
        i++;
    }
    map->height = height;
    map->width = width;
    //printf("first index: %d, last index: %d\n", map->first_index, map->last_index);
    //printf("first index line: %s\n", lines[map->first_index]);
    //printf("last index line: %s\n", lines[map->last_index]);
    //printf("map width: %d, and map height: %d\n", width, height);
}

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

int	handle_map(t_input *file_data, char **lines)
{
	if (init_map(file_data) == 1)
		return (1);
	get_map_properties(lines, file_data->map);
	if (!is_map_last_in_file(lines, file_data->map))
		return (1);
	file_data->map->grid = malloc(sizeof(char *) * (file_data->map->height + 1));
    if (!file_data->map->grid)
    {
        print_error("Memory allocation for map grid failed.");
        return (false);
    }
	if (!populate_grid(lines, file_data->map))
        return (false);
	if (!validate_map_characters(file_data->map))
        return (false);
	if (!is_map_surrounded_by_walls(file_data->map->grid))
        return (false);
    return (true);
}
