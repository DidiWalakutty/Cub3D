/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:28 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/03/19 18:04:43 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

bool is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}


static int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (1);
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

static int	check_map_sides(t_map *map, char **map_tab)
{
	size_t	i;
	size_t	j;

	if (check_top_or_bottom(map_tab, 0, 0) == 1)
		return (1);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (1);
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == 1)
		return (1);
	return (0);
}


bool	is_map_surrounded_by_walls(t_map *map)
{
	if (check_map_sides(map, map->grid) == 1)
		return (print_error("Map is not surrounded by walls."), false);
	
	return (true);
}

bool	validate_map_characters(t_map *map)
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
			free(trimmed_line);
			return (false);
		}
		free(trimmed_line);
		i++;
	}
	return (true);
}
