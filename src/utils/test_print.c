/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:17:09 by ykarimi           #+#    #+#             */
/*   Updated: 2025/03/23 12:06:41 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_parsed_content(t_input *content)
{
	int	i;

	printf("Parsed Content:\n");
	printf("North Texture: %s\n", content->north_texture);
	printf("South Texture: %s\n", content->south_texture);
	printf("West Texture: %s\n", content->west_texture);
	printf("East Texture: %s\n", content->east_texture);
	printf("Floor Color: %d, %d, %d\n", content->floor_colors[0], \
			content->floor_colors[1], content->floor_colors[2]);
	printf("Ceiling Color: %d, %d, %d\n", content->ceiling_colors[0], \
			content->ceiling_colors[1], content->ceiling_colors[2]);
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
