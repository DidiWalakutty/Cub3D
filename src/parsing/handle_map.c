/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 17:01:12 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/03/26 16:31:24 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_texture_or_color_line(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || \
			ft_strncmp(line, "SO ", 3) == 0 || \
			ft_strncmp(line, "WE ", 3) == 0 || \
			ft_strncmp(line, "EA ", 3) == 0 || \
			ft_strncmp(line, "F ", 2) == 0 || \
			ft_strncmp(line, "C ", 2) == 0);
}

static int	init_map(t_input *file_data)
{
	file_data->map = malloc(sizeof(t_map));
	if (!file_data->map)
	{
		print_error("map initialization failed.");
		return (1);
	}
	ft_bzero(file_data->map, sizeof(t_map));
	return (0);
}

static void	replace_spaces_with_one(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == ' ')
			{
				grid[i][j] = '1';
			}
			j++;
		}
		i++;
	}
}

static bool	validate_map(t_map *map)
{
	replace_spaces_with_one(map->grid);
	if (!validate_map_characters(map))
	{
		printf("Invalid map characters.");
		return (false);
	}
	if (!is_map_surrounded_by_walls(map))
	{
		print_error("Map is not surrounded by walls.");
		return (false);
	}
	if (is_player_entrapped(map))
	{
		print_error("Player is entrapped within walls.");
		return (false);
	}
	return (true);
}

bool	handle_map(t_input *data, char **lines)
{
	t_player	*player;

	if (init_map(data) == 1)
		return (false);
	get_map_properties(lines, data->map);
	if (!is_map_last_in_file(lines, data->map))
		return (false);
	data->map->grid = malloc(sizeof(char *) * (data->map->height + 1));
	if (!data->map->grid)
		return (print_error("Memory allocation failed."), false);
	ft_bzero(data->map->grid, sizeof(char *) * \
	(data->map->height + 1));
	if (!populate_grid(lines, data->map))
		return (print_error("Memory allocation failed."), false);
	player = malloc(sizeof(t_player));
	if (!player)
		return (false);
	data->map->player = player;
	ft_bzero(player, sizeof(t_player));
	set_player_spawning_point(data->map, player);
	if (check_player_spawning_point(player) == 1)
		return (false);
	if (validate_map(data->map) == false)
		return (false);
	return (true);
}
