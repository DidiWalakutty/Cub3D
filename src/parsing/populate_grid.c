/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_grid.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 11:20:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/03/26 16:22:31 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_no_spaces(char *no_spaces, const char *line)
{
	int	k;
	int	l;

	k = 0;
	l = 0;
	while (line[k] == ' ')
	{
		no_spaces[l] = '1';
		k++;
		l++;
	}
	while (line[k])
	{
		no_spaces[l] = line[k];
		k++;
		l++;
	}
	no_spaces[l] = '\0';
}

bool	populate_grid(char **lines, t_map *map)
{
	int		i;
	int		j;
	char	*no_spaces;

	i = map->first_index;
	j = 0;
	while (i <= map->last_index)
	{
		no_spaces = malloc(ft_strlen(lines[i]) + 1);
		if (!no_spaces)
		{
			print_error("Memory allocation for map grid line failed.");
			return (false);
		}
		fill_no_spaces(no_spaces, lines[i]);
		map->grid[j] = no_spaces;
		if (!map->grid[j])
			return (free(no_spaces), false);
		i++;
		j++;
	}
	map->grid[j] = NULL;
	return (true);
}
