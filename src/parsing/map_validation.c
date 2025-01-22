#include "cub3d.h"

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	is_map_surrounded_by_walls(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || i == ft_strlen(map[i]) - 1 || j == 0 || j == ft_strlen(map[i]) - 1) && map[i][j] != '1')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
bool	validate_textures(t_input *content)
{
	if (!content->north_texture)
	{
		printf("Missing North Texture\n");
		return false;
	}
	if (!content->south_texture)
	{
		printf("Missing South Texture\n");
		return false;
	}
	if (!content->west_texture)
	{
		printf("Missing West Texture\n");
		return false;
	}
	if (!content->east_texture)
	{
		printf("Missing East Texture\n");
		return false;
	}
	return true;
}
