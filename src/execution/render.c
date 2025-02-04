/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:22:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/03 13:18:29 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_direction(t_render *render)
{
	
}

// Update raycast/render info
void	update_raycast_vars(t_cub3d *cub3d, t_render *ray, size_t screen_i)
{
	ray->camera_column = 2 * ((double)screen_i / (double)S_WIDTH) - 1;
	ray->plane.x = ray->player_direction.x + (ray->plane.x * ray->camera_column);
	ray->plane.y = ray->player_direction.y + (ray->plane.y * ray->camera_column);
	ray->map_pos.x = (int32_t)ray->player_pos.x;
	ray->map_pos.y = (int32_t)ray->player_pos.y;
	// check plane x and y for 0???
	// if/else statement. Fab?
	update_direction(render);
	// find wall: DDA thing with shortest length for grid: x or y - check if hit wall.
	// set lines
}
