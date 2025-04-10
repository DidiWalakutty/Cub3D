/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:31:51 by yasamankari       #+#    #+#             */
/*   Updated: 2025/04/06 10:15:28 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_empty_or_texture_line(const char *line, bool *map_started)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (!trimmed_line)
		return (false);
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
		if (!is_empty_or_texture_line(lines[i], &map_started))
		{
			if (map_started)
				break ;
			print_error("Error processing non-map lines.");
			return (-1);
		}
		i++;
	}
	return (i);
}

bool	update_map_dimensions(const char *line, t_map *map, int i)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > (int)map->width)
		map->width = line_len;
	map->height++;
	map->last_index = i;
	return (true);
}

bool	process_single_map_line(const char *line, t_map *map, int i)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (!trimmed_line)
		return (false);
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (true);
	}
	if (is_valid_map_char(trimmed_line[0]))
	{
		if (!update_map_dimensions(trimmed_line, map, i))
			return (free(trimmed_line), false);
	}
	else
		return (free(trimmed_line), false);
	free(trimmed_line);
	return (true);
}

bool	get_map_properties(char **lines, t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->first_index = skip_non_map_lines(lines);
	if (map->first_index == -1)
		return (false);
	if (!process_map_lines(lines, map))
		return (false);
	return (true);
}
