/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_grid.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 11:20:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/03/26 12:59:07 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*trim_and_allocate(const char *line, size_t width)
{
	char	*trimmed;
	char	*no_spaces;

	trimmed = ft_strtrim(line, " \t\n\r");
	no_spaces = malloc(width + 1);
	if (!no_spaces)
	{
		print_error("Memory allocation for map grid line failed.");
		free(trimmed);
		return (NULL);
	}
	free(trimmed);
	return (no_spaces);
}

static void	fill_no_spaces(char *no_spaces, const char *line, const char *trimmed)
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
	while (trimmed[l - k])
	{
		no_spaces[l] = trimmed[l - k];
		l++;
	}
	no_spaces[l] = '\0';
}

bool	populate_grid(char **lines, t_map *map)
{
	int		i;
	int		j;
	char	*trimmed;
	char	*no_spaces;

	i = map->first_index;
	j = 0;
	while (i <= map->last_index)
	{
		trimmed = ft_strtrim(lines[i], " \t\n\r");
		no_spaces = trim_and_allocate(lines[i], map->width);
		if (!no_spaces)
			return (false);
		fill_no_spaces(no_spaces, lines[i], trimmed);
		map->grid[j] = no_spaces;
		if (!map->grid[j])
		{
			free(trimmed);
			return (free(no_spaces), false);
		}
		i++;
		j++;
		free(trimmed);
	}
	map->grid[j] = NULL;
	return (true);
}
