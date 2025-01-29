/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:28 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/29 10:17:10 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool is_map_surrounded_by_walls(char **map)
{
    size_t row_index;
    size_t col_index;
    size_t last_row_index;
    size_t last_col_index;

    // Calculate the last row and column indices
    last_row_index = 0;
    while (map[last_row_index])
        last_row_index++;
    last_row_index--;

    // Trim trailing whitespace lines
    while (last_row_index > 0 && ft_strlen(ft_strtrim(map[last_row_index], " \t\n\r")) == 0)
        last_row_index--;

    last_col_index = ft_strlen(map[0]) - 1;

    // Check the first and last rows
    for (col_index = 0; col_index <= last_col_index; col_index++)
    {
        if (map[0][col_index] != '1')
        {
            printf("First row not surrounded by walls at col_index: %zu, char: %c\n", col_index, map[0][col_index]);
            return (print_error("Map is not surrounded by walls."), false);
        }
        if (map[last_row_index][col_index] != '1')
        {
            printf("Last row not surrounded by walls at col_index: %zu, char: %c\n", col_index, map[last_row_index][col_index]);
            return (print_error("Map is not surrounded by walls."), false);
        }
    }

    // Check the first and last columns of each row
    for (row_index = 0; row_index <= last_row_index; row_index++)
    {
        if (map[row_index][0] != '1')
        {
            printf("First column not surrounded by walls at row_index: %zu, char: %c\n", row_index, map[row_index][0]);
            return (print_error("Map is not surrounded by walls."), false);
        }
        if (map[row_index][last_col_index] != '1')
        {
            printf("Last column not surrounded by walls at row_index: %zu, char: %c\n", row_index, map[row_index][last_col_index]);
            return (print_error("Map is not surrounded by walls."), false);
        }
    }

    return true;
}


// bool	is_map_surrounded_by_walls(char **map)
// {
// 	size_t	row_index;
// 	size_t	col_index;

// 	row_index = 0;
// 	while (map[row_index])
// 	{
// 		col_index = 0;
// 		while (map[row_index][col_index])
// 		{
// 			if ((row_index == 0 || row_index == ft_strlen(map[row_index]) - 1 || col_index == 0 || col_index == ft_strlen(map[row_index]) - 1) && map[row_index][col_index] != '1')
// 				return (print_error("Map is not surrounded by walls."), false);
// 			col_index++;
// 		}
// 		row_index++;
// 	}
// 	return (true);
// }




bool	validate_map_characters(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (!is_valid_map_char(map->grid[i][j]))
            {
                printf("map char: %c\n", map->grid[i][j]);
                print_error("Invalid map character.");
                return (false);
            }
			j++;
		}
		i++;
	}
	return (true);
}


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
            //printf("Illegal map content found after the map at line %d: %s\n", i, trimmed_line);
            free(trimmed_line);
            return (false);
        }
        free(trimmed_line);
        i++;
    }
    return (true);
}