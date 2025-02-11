/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 15:39:23 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/04 15:39:23 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	hit_wall(char **grid, t_map *map, int32_t y, int32_t x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (true);
	return (grid[y][x] == '1');
}

// Checks if the new position is free by testing both a forward and backward 
// Need offset using WALL_MARGIN to prevent collisions??? : new.y + WALL_MARGIN * dir.y
bool	path_clear(char **grid, t_map *map, t_dvectr new)
{
	double	margin;

	margin = 0.1;
	if (hit_wall(grid, map, (int32_t)(new.y + margin), (int32_t)(new.x)))
		return (false);
	if (hit_wall(grid, map, (int32_t)(new.y - margin), (int32_t)(new.x)))
		return (false);
	if (hit_wall(grid, map, (int32_t)(new.y), (int32_t)(new.x + margin)))
		return (false);
	if (hit_wall(grid, map, (int32_t)(new.y), (int32_t)(new.x - margin)))
		return (false);
	return (true);
}
