/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:42 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/03/19 14:25:17 by ykarimi       ########   odam.nl         */
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

bool	extract_elements(char **lines, t_input *content, bool *has_floor_color, bool *has_ceiling_color)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	while (lines[i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		{
			if (!parse_color(trimmed_line, content->floor_colors))
				return (free(trimmed_line), false);
			*has_floor_color = true;
		}
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			if (!parse_color(trimmed_line, content->ceiling_colors))
				return (free(trimmed_line), false);
			*has_ceiling_color = true;
		}
		else if (is_texture_prefix(trimmed_line))
		{
			if (!parse_texture(trimmed_line, content))
				return (free(trimmed_line), false);
		}
		free(trimmed_line);
		i++;
	}
	return (true);
}

static void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

/*
not sure if i need to keep the end_index isntead (whihc one makes more sense and is more handy)
*/
int	parse_file(char *argv[], t_input *file_data)
{
	char	**lines;
	int		result;
	bool has_floor_color;
	bool has_ceiling_color;

	lines = NULL;
	result = 0;
	result = handle_input(argv[1], &lines);
	if (result != 0)
	{
		if (lines)
			free_lines(lines);
		return (result);
	}
	if (!extract_elements(lines, file_data, &has_floor_color, &has_ceiling_color))
		result = 1;
	else
	{
		if(!handle_map(file_data, lines))
			result = 1;
	}
	if (!validate_textures(file_data))
		result = 1;	
	if (lines)
		free_lines(lines);
	if (!has_ceiling_color || !has_floor_color)
	{
		print_error("Both floor and ceiling colors must be specified.");
		result = 1;
	}
	return (result);
}
