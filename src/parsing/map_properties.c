/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_properties.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 11:31:51 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/03/26 16:31:05 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_empty_or_texture_line(const char *line, bool *map_started)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (true);
	}
	if (!*map_started && is_texture_or_color_line(trimmed_line))
	{
		free(trimmed_line);
		return (true);
	}
	*map_started = true;
	free(trimmed_line);
	return (false);
}

static int	skip_non_map_lines(char **lines)
{
	int		i;
	bool	map_started;

	i = 0;
	map_started = false;
	while (lines[i])
	{
		if (is_empty_or_texture_line(lines[i], &map_started))
		{
			i++;
			continue ;
		}
		break ;
	}
	return (i);
}

static void	update_map_dimensions(const char *line, t_map *map, int i)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > (int)map->width)
		map->width = line_len;
	map->height++;
	map->last_index = i;
}

static void	process_map_lines(char **lines, t_map *map)
{
	int		i;
	char	*trimmed_line;

	i = map->first_index;
	while (lines[i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		if (trimmed_line[0] == '\0')
		{
			free(trimmed_line);
			i++;
			continue ;
		}
		if (is_valid_map_char(trimmed_line[0]))
			update_map_dimensions(trimmed_line, map, i);
		free(trimmed_line);
		i++;
	}
}

void	get_map_properties(char **lines, t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->first_index = skip_non_map_lines(lines);
	process_map_lines(lines, map);
}
