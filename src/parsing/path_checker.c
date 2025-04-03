/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 11:36:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/04/03 16:10:49 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	can_move_direction(t_map *map, int dx, int dy)
{
	size_t	new_x;
	size_t	new_y;

	new_x = map->player->x + dx;
	new_y = map->player->y + dy;
	if (new_x > 0 && new_x < map->width - 1 && \
		new_y > 0 && new_y < map->height - 1 && \
		map->grid[new_y][new_x] != '1')
		return (true);
	else
		return (false);
}

bool	is_player_entrapped(t_map *map)
{
	if (!can_move_direction(map, 0, 1) && \
		!can_move_direction(map, 0, -1) && \
		!can_move_direction(map, 1, 0) && \
		!can_move_direction(map, -1, 0))
		return (true);
	else
		return (false);
}
