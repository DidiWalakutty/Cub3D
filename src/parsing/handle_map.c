/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:12 by ykarimi           #+#    #+#             */
/*   Updated: 2025/03/23 11:01:30 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	populate_grid(char **lines, t_map *map)
{
    int i;
    int j;
    char *trimmed;
    char *no_spaces;

    i = map->first_index;
    j = 0;
    while (i <= map->last_index)
    {
        trimmed = ft_strtrim(lines[i], " \t\n\r");
        no_spaces = malloc(map->width + 1);
        if (!no_spaces)
        {
            print_error("Memory allocation for map grid line failed.");
            free(trimmed);
            return false;
        }
        int k = 0;
        int l = 0;
        while (lines[i][k] == ' ')
        {
            no_spaces[l] = '1';
            k++;
            l++;
        }
        while (trimmed[l - k])
        {
            no_spaces[l] = trimmed[l - k];
            l++;
        }
        no_spaces[l] = '\0';
        map->grid[j] = no_spaces;
        if (!map->grid[j])
        {
            print_error("Memory allocation for map grid line failed.");
            free(trimmed);
            free(no_spaces);
            return false;
        }
        i++;
        j++;
        free(trimmed);
    }
    map->grid[j] = NULL;
    return true;
}




static int skip_non_map_lines(char **lines)
{
    int i = 0;
    bool map_started = false;

    while (lines[i])
    {
        char *trimmed_line = ft_strtrim(lines[i], " \t\n\r");
        if (trimmed_line[0] == '\0')
        {
            free(trimmed_line);
            i++;
            continue;
        }
        if (!map_started && (ft_strncmp(trimmed_line, "NO ", 3) == 0 || 
                             ft_strncmp(trimmed_line, "SO ", 3) == 0 || 
                             ft_strncmp(trimmed_line, "WE ", 3) == 0 || 
                             ft_strncmp(trimmed_line, "EA ", 3) == 0 || 
                             ft_strncmp(trimmed_line, "F ", 2) == 0 || 
                             ft_strncmp(trimmed_line, "C ", 2) == 0))
        {
            free(trimmed_line);
            i++;
            continue;
        }
        map_started = true;
        int j = 0;
        while (trimmed_line[j] == ' ')
        {
            trimmed_line[j] = '1';
            j++;
        }
        if (is_valid_map_char(trimmed_line[j]))
        {
            free(trimmed_line);
            break;
        }

        free(trimmed_line);
        i++;
    }
    return i;
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
		 if (trimmed_line[0] == '\0')
        {
            free(trimmed_line);
            i++;
            continue;
        }
        if (trimmed_line[0] != '\0' && is_valid_map_char(trimmed_line[0]))
        {
            line_len = ft_strlen(trimmed_line);
            if (line_len > width)
                width = line_len;
            height++;
            map->last_index = i;
        }
        free(trimmed_line);
        i++;
    }
    map->height = height;
    map->width = width;
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

static void replace_spaces_with_one(char **grid)
{
    int i, j;

    i = 0;
    while (grid[i])
    {
        j = 0;
        while (grid[i][j])
        {
            if (grid[i][j] == ' ')
            {
                grid[i][j] = '1';
            }
            j++;
        }
        i++;
    }
}

static bool	validate_map(t_map *map)
{
	replace_spaces_with_one(map->grid);
	if (!validate_map_characters(map))
	{
		printf("Invalid map characters.");
		return (false);
	}
	if (!is_map_surrounded_by_walls(map))
	{
		print_error("Map is not surrounded by walls.");
		return (false);
	}
	if (is_player_entrapped(map))
	{
		print_error("Player is entrapped within walls.");
		return (false);
	}
	return (true);
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
		return (print_error("Memory allocation for map grid failed."), false);
	ft_bzero(file_data->map->grid, sizeof(char *) * (file_data->map->height + 1));	
	if (!populate_grid(lines, file_data->map))
		return (false);
	player = malloc(sizeof(t_player));
	if (!player)
		return (false);
	file_data->map->player = player;
	ft_bzero(player, sizeof(t_player));
	set_player_spawning_point(file_data->map, player);
	if (check_player_spawning_point(player) == 1)
		return (false);
	if (validate_map(file_data->map) == false)
		return (false);
	return (true);
}
