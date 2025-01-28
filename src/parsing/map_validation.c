/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:28 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/28 14:00:19 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	is_map_surrounded_by_walls(char **map)
{
	size_t	row_index;
	size_t	col_index;

	row_index = 0;
	while (map[row_index])
	{
		col_index = 0;
		while (map[row_index][col_index])
		{
			if ((row_index == 0 || row_index == ft_strlen(map[row_index]) - 1 || col_index == 0 || col_index == ft_strlen(map[row_index]) - 1) && map[row_index][col_index] != '1')
				return (false);
			col_index++;
		}
		row_index++;
	}
	return (true);
}
bool	validate_textures(t_input *content)
{
	if (!content->north_texture)
	{
		printf("Missing North Texture\n");
		return (false);
	}
	if (!content->south_texture)
	{
		printf("Missing South Texture\n");
		return (false);
	}
	if (!content->west_texture)
	{
		printf("Missing West Texture\n");
		return (false);
	}
	if (!content->east_texture)
	{
		printf("Missing East Texture\n");
		return (false);
	}
	return (true);
}

