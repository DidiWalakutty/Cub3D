/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_print.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:17:09 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/28 13:58:56 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	print_parsed_content(t_input *content)
{
	int i;

	printf("Parsed Content:\n");

	// Print textures
	printf("North Texture: %s\n", content->north_texture);
	printf("South Texture: %s\n", content->south_texture);
	printf("West Texture: %s\n", content->west_texture);
	printf("East Texture: %s\n", content->east_texture);

	// Print colors
	printf("Floor Color: %d, %d, %d\n", content->floor_colors[0], content->floor_colors[1], content->floor_colors[2]);
	printf("Ceiling Color: %d, %d, %d\n", content->ceiling_colors[0], content->ceiling_colors[1], content->ceiling_colors[2]);

	// Print map
	printf("Map:\n");
	i = 0;
	if (content->map && content->map->grid)
	{
		while (content->map->grid[i])
		{
			printf("%s\n", content->map->grid[i]);
			i++;
		}
	}
}

void	print_map(char **map)
{
	int row_index = 0;

	printf("Map:\n");
	while (map[row_index])
	{
		printf("%s\n", map[row_index]);
		row_index++;
	}
}
