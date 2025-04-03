/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:28 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/04/03 16:12:51 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' \
			|| c == 'W' || c == ' ');
}

bool	validate_map_characters(t_map *map)
{
	int	i;
	int	j;

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
		if (!trimmed_line)
			return (false);
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
