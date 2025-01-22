#include "cub3d.h"

bool	is_file_empty(char *file_content)
{
	while (*file_content)
	{
		if (!ft_isspace((unsigned char)*file_content))
			return (false);
		file_content++;
	}
	return (true);
}

bool	extract_elements_from_file(char **lines, t_input *content, int *map_start_index)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	while (lines[i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
		//printf("Processing line: %s\n", trimmed_line);
		if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		{
			if (!parse_color(trimmed_line, content->floor_colors))
			{
				printf("Parse color for floor failed\n");
				free(trimmed_line);
				return (false);
			}
		}
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			if (!parse_color(trimmed_line, content->ceiling_colors))
			{
				printf("Parse color for ceiling failed\n");
				free(trimmed_line);
				return (false);
			}
		}
		else if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line, "SO ", 3) == 0 ||
				ft_strncmp(trimmed_line, "WE ", 3) == 0 || ft_strncmp(trimmed_line, "EA ", 3) == 0)
		{
			if (!parse_texture(trimmed_line, content))
			{
				printf("Parse texture failed for line: %s\n", trimmed_line);
				free(trimmed_line);
				return (false);
			}
		}
		else if (is_valid_map_char(trimmed_line[0]))
		{
			*map_start_index = i;
			printf("Finished parsing elements at line: %d\n", i);
			free(trimmed_line);
			return (true);
		}
		else if (trimmed_line[0] != '\0')
		{
			printf("Invalid line: %s\n", trimmed_line);
			free(trimmed_line);
			return (false);
		}
		free(trimmed_line);
		i++;
	}
	*map_start_index = i;
	return (true);
}


int	parse_file(char *argv[], t_input *file_data)
{
	char	**lines;
	int		map_start_index;
	int		result;

	lines = NULL;
	result = 0;
	if (validate_map_extension(argv[1]) == 1)
		return (1);
	result = handle_input(argv[1], &lines);
	if (result != 0)
		return result;
	if (!extract_elements_from_file(lines, file_data, &map_start_index))
	{
		printf("Extract elements from file failed\n");
		result = 1;
	}
	else if (!validate_textures(file_data))
	{
		printf("Texture validation failed\n");
		result = 1;
	}
	else if (lines[map_start_index] == NULL || !is_valid_map_char(lines[map_start_index][0]))
	{
		printf("Map content is missing or invalid\n");
		result = 1;
	}
	else if (!parse_map(lines, file_data, map_start_index))
	{
		printf("Parse map failed\n");
		result = 1;
	}
	else
	{
		printf("Parsing completed successfully.\n");
	}
	// populate map data
	printf("-----------------\n\n");
	print_parsed_content(file_data);
	printf("-----------------\n\n");
	return (result);
}
