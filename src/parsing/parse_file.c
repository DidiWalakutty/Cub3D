/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:42 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/29 10:31:21 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_texture_prefix(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 ||
			ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 ||
			ft_strncmp(line, "EA ", 3) == 0);
}

bool	extract_elements(char **lines, t_input *content)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	while (lines[i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		//printf("trimmed line in extract func: %s\n", trimmed_line);
		if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		{
			if (!parse_color(trimmed_line, content->floor_colors))
				return (free(trimmed_line), false);
		}
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			if (!parse_color(trimmed_line, content->ceiling_colors))
				return (free(trimmed_line), false);
		}
		else if (is_texture_prefix(trimmed_line))
		{
			//printf("trimmed line in extract func before pars text: %s\n", trimmed_line);
			if (!parse_texture(trimmed_line, content))
				return (free(trimmed_line), false);
		}
		free(trimmed_line);
		i++;
	}
	return (true);
}



/*
not sure if i need to keep the end_index isntead (whihc one makes more sense and is more handy)
*/
int	parse_file(char *argv[], t_input *file_data)
{
	char	**lines;
	int		result;

	lines = NULL;
	result = 0;
	result = handle_input(argv[1], &lines);
	if (result != 0)
		return (result);
	if (!extract_elements(lines, file_data))
		result = 1;
	else
	{
		if(handle_map(file_data, lines))
			result = 1;
	}
	if (!validate_textures(file_data))
		return (false);
	return (result);
}
