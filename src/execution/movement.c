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

bool	hit_wall(char **grid, int32_t x, int32_t y)
{
	return (grid[x][y] == '1');
}

// Checks if the new position is free by testing both a forward and backward 
// offset using WALL_MARGIN to prevent collisions.
bool	path_clear(char **grid, t_dvectr player_pos, t_dvectr new, t_dvectr dir)
{
	if (hit_wall(grid, (int32_t)(new.x + WALL_MARGIN * dir.x), \
						(int32_t)(new.y + WALL_MARGIN * dir.y)))
		return (false);
	if (hit_wall(grid, (int32_t)(new.x - WALL_MARGIN * dir.x), \
						(int32_t)(new.y - WALL_MARGIN * dir.y)))
		return (false);
	return (true);
}