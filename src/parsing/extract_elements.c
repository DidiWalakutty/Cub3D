/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_elements.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 11:14:41 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/04/03 16:34:11 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	process_texture_line(char *line, t_input *content)
{
	if (!handle_texture(line, content))
		return (false);
	return (true);
}

int	process_element_line(char *line, t_input *content, \
							bool *f_color, bool *c_color)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (process_floor_line(line, content, f_color))
			return (1);
		else
			return (0);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (process_ceiling_line(line, content, c_color))
			return (1);
		else
			return (0);
	}
	else if (is_texture_prefix(line))
	{
		if (process_texture_line(line, content))
			return (1);
		else
			return (0);
	}
	return (-1);
}

int	process_map_or_empty_line(char *line)
{
	if (line[0] == '\0')
		return (1);
	else if (is_valid_map_char(line[0]))
		return (STOP_PROCESSING);
	return (0);
}

int	process_line(char *line, t_input *content, bool *f_color, bool *c_color)
{
	int	result;

	result = process_element_line(line, content, f_color, c_color);
	if (result != -1)
		return (result);
	return (process_map_or_empty_line(line));
}

bool	extract_elements(char **lines, t_input *content, \
							bool *f_color, bool *c_color)
{
	int		i;
	char	*trimmed_line;
	int		result;

	i = -1;
	while (lines[++i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		if (!trimmed_line)
			return (false);
		result = process_line(trimmed_line, content, f_color, c_color);
		free(trimmed_line);
		if (result == 0)
			return (false);
		else if (result == STOP_PROCESSING)
			break ;
	}
	return (true);
}
