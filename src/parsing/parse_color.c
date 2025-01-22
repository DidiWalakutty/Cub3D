#include "cub3d.h"
#include "libft.h"

static	bool split_rgb_values(char *line, char ***rgb)
{
	*rgb = ft_split(line + 2, ',');
	if (!*rgb)
	{
		printf("Failed to split color line: %s\n", line);
		return (false);
	}
	return (true);
}

static	bool validate_rgb_values(char **rgb, int *color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!rgb[i])
		{
			printf("Missing RGB value at position %d\n", i);
			return false;
		}
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			printf("Invalid color value: %d\n", color[i]);
			return false;
		}
		i++;
	}
	if (rgb[i] != NULL)
	{
		printf("Too many RGB values\n");
		return false;
	}
	return true;
}

bool	parse_color(char *line, int *color)
{
	char	**rgb;
	char	*trimmed_line;

	printf("Parsing color line: %s\n", line);
	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (!split_rgb_values(trimmed_line, &rgb))
	{
		free(trimmed_line);
		return false;
	}
	if (!validate_rgb_values(rgb, color))
	{
		free(trimmed_line);
		return false;
	}
	printf("Parsed Color: %d, %d, %d\n", color[0], color[1], color[2]);
	free(trimmed_line);
	return true;
}
