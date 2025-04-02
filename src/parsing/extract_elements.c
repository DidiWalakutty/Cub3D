/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_elements.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 11:14:41 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/04/02 12:23:42 by ykarimi       ########   odam.nl         */
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
	printf("Processing texture line: '%s'\n", line);
	return (parse_texture(line, content));
}

// static bool f_c(char *trimmed_line, t_input *content, bool *f_color, bool *c_color)
// {
// 	if (ft_strncmp(trimmed_line, "F ", 2) == 0)
// 		{
// 			if (!handle_floor_color(trimmed_line, content, f_color))
// 				return (free(trimmed_line), false);
// 		}
// 		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
// 		{
// 			if (!handle_ceiling_color(trimmed_line, content, c_color))
// 				return (free(trimmed_line), false);
// 		}
// 		return true;
	
// }


bool	extract_elements(char **lines, t_input *content, \
						bool *f_color, bool *c_color)
{
	int		i;
	char	*trimmed_line;

	i = -1;
	while (lines[++i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		if (!trimmed_line)
			return (false);
		// if (!f_c(trimmed_line, content, f_color, c_color))
		// {
		// 	return (free(trimmed_line), false);
		// }
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
		else if (trimmed_line[0] == '\0')
		{
			free(trimmed_line);
			continue ;
		}
		else if (is_valid_map_char(trimmed_line[0]))
        {
            free(trimmed_line);
            break;
        }
		else
			return (free(trimmed_line), false);
		free(trimmed_line);
	}
	return (true);
}


