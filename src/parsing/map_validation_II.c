/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation_II.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 11:48:13 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/03/26 13:43:41 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_line_for_walls(const char *line)
{
    int	j;

	j = 0;
    while (line[j] == ' ' || line[j] == '\t' || line[j] == '\r' || \
			line[j] == '\v' || line[j] == '\f')
        j++;
    while (line[j])
    {
        if (line[j] != '1')
            return (false);
        j++;
    }
    return (true);
}

static bool	check_top_and_bottom_walls(char **grid, int row)
{
    if (!grid || !grid[row])
        return (false);
    return (check_line_for_walls(grid[row]));
}

static bool	check_side_walls(t_map *map, char **grid)
{
    size_t i;
    size_t j;

    for (i = 1; i < map->height - 1; i++)
    {
        j = ft_strlen(grid[i]) - 1;
        if (grid[i][0] != '1' || grid[i][j] != '1')
            return (false);
    }
    return (true);
}

bool	is_map_surrounded_by_walls(t_map *map)
{
    if (!check_top_and_bottom_walls(map->grid, 0) || \
	!check_top_and_bottom_walls(map->grid, map->height - 1))
        return (false);
    if (!check_side_walls(map, map->grid))
        return (false);
    return (true);
}
