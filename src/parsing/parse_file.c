/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:42 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/04/03 16:12:21 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	handle_input_and_extract_elements(char *file, char ***lines, \
													t_input *file_data)
{
	int	result;

	result = handle_input(file, lines);
	if (result != 0)
	{
		if (*lines)
			free_lines(*lines);
		return (result);
	}
	if (!extract_elements(*lines, file_data, &file_data->has_floor_color, \
						&file_data->has_ceiling_color))
		return (1);
	return (0);
}

static int	handle_map_and_validate(t_input *file_data, char **lines)
{
	if (!handle_map(file_data, lines))
		return (1);
	if (!validate_textures(file_data))
		return (1);
	return (0);
}

int	parse_file(char *argv[], t_input *file_data)
{
	char	**lines;
	int		result;

	lines = NULL;
	result = handle_input_and_extract_elements(argv[1], &lines, file_data);
	if (result == 0)
		result = handle_map_and_validate(file_data, lines);
	if (lines)
		free_lines(lines);
	if (result != 0)
		print_error("Problem with extracting elements.");
	if (!file_data->has_ceiling_color || !file_data->has_floor_color)
	{
		print_error("Both floor and ceiling colors must be specified.");
		result = 1;
	}
	return (result);
}
