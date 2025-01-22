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
