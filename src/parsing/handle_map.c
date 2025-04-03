/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 17:01:12 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/04/03 16:49:59 by ykarimi       ########   odam.nl         */
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
// malloc check
static void	replace_spaces_with_one(char **grid)
{
    int	i;
    int	j;
    int	max_length;

    max_length = 0;
    i = 0;
    while (grid[i])
    {
        int line_length = ft_strlen(grid[i]);
        if (line_length > max_length)
            max_length = line_length;
        i++;
    }
    i = 0;
    while (grid[i])
    {
        j = 0;
        while (grid[i][j])
        {
            if (grid[i][j] == ' ')
                grid[i][j] = '1';
            j++;
        }
        if (j < max_length)
        {
            char *padded_line = malloc(max_length + 1);
            if (!padded_line)
            {
                print_error("Memory allocation failed while padding lines.");
                return ;
            }
            ft_strlcpy(padded_line, grid[i], max_length + 1);
            while (j < max_length)
                padded_line[j++] = '1';
            padded_line[j] = '\0';
            free(grid[i]);
            grid[i] = padded_line;
        }
        i++;
    }
}


static bool	validate_map(t_map *map)
{
	replace_spaces_with_one(map->grid);
	if (!validate_map_characters(map))
		return (false);
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
