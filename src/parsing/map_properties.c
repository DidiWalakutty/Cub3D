/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:31:51 by yasamankari       #+#    #+#             */
/*   Updated: 2025/03/23 12:03:05 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_texture_or_color_line(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || 
			ft_strncmp(line, "SO ", 3) == 0 || 
			ft_strncmp(line, "WE ", 3) == 0 || 
			ft_strncmp(line, "EA ", 3) == 0 || 
			ft_strncmp(line, "F ", 2) == 0 || 
			ft_strncmp(line, "C ", 2) == 0);
}

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
			continue;
		}
		break;
	}
	return (i);
}

static void	update_map_dimensions(const char *line, int *width, \
							int *height, int *last_index, int i)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > *width)
		*width = line_len;
	(*height)++;
	*last_index = i;
}

void	get_map_properties(char **lines, t_map *map)
{
	int		height;
	int		width;
	int		i;
	char	*trimmed_line;

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
		if (is_valid_map_char(trimmed_line[0]))
			update_map_dimensions(trimmed_line, &width, &height, &map->last_index, i);
		free(trimmed_line);
		i++;
	}
	map->height = height;
	map->width = width;
}
