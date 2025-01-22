#include "cub3d.h"

bool	is_map_last_in_file(char **lines, int map_start_index)
{
	int i = map_start_index;

	while (lines[i])
	{
		if (lines[i][0] != '\0' && !is_valid_map_char(lines[i][0]))
		{
			printf("Error: Non-map content found after map content at line %d\n", i);
			return (false);
		}
		i++;
	}
	return (true);
}


bool	parse_map(char **lines, t_input *content, int map_start_index)
{
	int	i;
	int	j;

	printf("Inside parse map\n");
	i = map_start_index;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (!is_valid_map_char(lines[i][j]))
			{
				printf("Invalid map character: %c\n", lines[i][j]);
				return (false);
			}
			j++;
		}
		i++;
	}

	// Check if the map content is the last part of the file
	if (!is_map_last_in_file(lines, map_start_index))
	{
		printf("Error: Map content is not the last part of the file\n");
		return (false);
	}

	content->map = malloc(sizeof(t_map));
	content->map->grid = lines + map_start_index;
	if (!is_map_surrounded_by_walls(content->map->grid))
	{
		printf("Map is not surrounded by walls\n");
		return (false);
	}
	printf("Parsed Map:\n");
	i = 0;
	while (content->map->grid[i])
	{
		printf("%s\n", content->map->grid[i]);
		i++;
	}
	return (true);
}
