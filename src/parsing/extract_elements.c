/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_elements.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 11:14:41 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/03/26 13:58:37 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_texture_prefix(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || \
			ft_strncmp(line, "SO ", 3) == 0 || \
			ft_strncmp(line, "WE ", 3) == 0 || \
			ft_strncmp(line, "EA ", 3) == 0);
}

static bool	handle_floor_color(char *line, t_input *content, \
	bool *f_color)
{
	if (!parse_color(line, content->floor_colors))
		return (false);
	*f_color = true;
	return (true);
}

static bool	handle_ceiling_color(char *line, t_input *content, \
	bool *c_color)
{
	if (!parse_color(line, content->ceiling_colors))
		return (false);
	*c_color = true;
	return (true);
}

static bool	handle_texture(char *line, t_input *content)
{
	return (parse_texture(line, content));
}

bool	extract_elements(char **lines, t_input *content, \
						bool *f_color, bool *c_color)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	while (lines[i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		{
			if (!handle_floor_color(trimmed_line, content, f_color))
				return (free(trimmed_line), false);
		}
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			if (!handle_ceiling_color(trimmed_line, content, c_color))
				return (free(trimmed_line), false);
		}
		else if (is_texture_prefix(trimmed_line))
		{
			if (!handle_texture(trimmed_line, content))
				return (free(trimmed_line), false);
		}
		free(trimmed_line);
		i++;
	}
	return (true);
}
