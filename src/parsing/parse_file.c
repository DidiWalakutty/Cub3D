/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:42 by ykarimi           #+#    #+#             */
/*   Updated: 2025/02/13 15:35:37 by yasamankari      ###   ########.fr       */
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
	//bool	has_floor_color;
	//bool	has_ceiling_color;

	//has_floor_color = false;
	//has_ceiling_color = false;
	i = 0;
	while (lines[i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		//printf("trimmed line in extract func: %s\n", trimmed_line);
		if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		{
			//printf("trimmed line in extract func - F: %s\n", trimmed_line);
			if (!parse_color(trimmed_line, content->floor_colors))
				return (free(trimmed_line), false);
			//has_floor_color = true;
		}
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			//printf("trimmed line in extract func - C: %s\n", trimmed_line);
			if (!parse_color(trimmed_line, content->ceiling_colors))
				return (free(trimmed_line), false);
			//has_floor_color = true;
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
	// if (!has_floor_color || !has_ceiling_color)
    //     return (print_error("Both floor and ceiling colors must be specified"), false);
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
	//bool has_floor_color;
	//bool has_ceiling_color;

	lines = NULL;
	result = 0;
	result = handle_input(argv[1], &lines);
	if (result != 0)
	{
		if (lines)
			free_lines(lines);
		return (result);
	}
	if (!extract_elements(lines, file_data))
		result = 1;
	else
	{
		// if (!file_data->floor_colors[0] || !file_data->ceiling_colors[0])
    	// {
        // 	printf("Both floor and ceiling colors must be specified\n");
        // 	result = 1;
    	// }
		if(!handle_map(file_data, lines))
			result = 1;
	}
	if (!validate_textures(file_data))
		result = 1;	
	if (lines)
		free_lines(lines);
	if (!file_data->floor_colors[0] || !file_data->ceiling_colors[0])
    {
        printf("Both floor and ceiling colors must be specified\n");
        result = 1;
    }
	printf("status of parsing_file function: %d\n", result);
	return (result);
}
