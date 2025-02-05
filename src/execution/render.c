/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:22:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/05 17:39:58 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calcs side distances and if the ray hits a wall.
// Determines which direction (x or y) to step in next. 
// Based on which side distance is shorter.
static void	dda_algorithm(t_render *ray, t_cub3d *cub3d)
{
	while (1)
	{
		if (ray->side_dist.y < ray->side_dist.x)
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->wall_side = X_SIDE;
		}
		else
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->wall_side = Y_SIDE;
		}
		if (hit_wall(cub3d->map_data->grid, ray->map_pos.x, ray->map_pos.y))
			break ;
	}
}

// Calcs the step direction and initial side distances for both axes, based
// on the player_pos and ray_dir. Determines whether the ray is moving up/down
// or left/right and updates the step values.
static void	update_direction(t_render *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->player_pos.x - ray->map_pos.x) * \
							ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->player_pos.x + 1.0 - ray->player_pos.x) * \
							ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->player_pos.y - ray->map_pos.y) * \
							ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->player_pos.y + 1.0 - ray->player_pos.y) * \
							ray->delta_dist.y;
	}
}

// Generates a new ray.
// Calcs the camera coordinate, updates ray direction and sets pos in map.
// Calcs the delta distance (how much a ray moves in each step) for x and y.
void	create_ray(t_cub3d *cub3d, t_render *ray, size_t screen_i)
{
	ray->camera_column = 2 * ((double)screen_i / (double)S_WIDTH) - 1;
	ray->ray_dir.x = ray->player_dir.x + (ray->plane.x * ray->camera_column);
	ray->ray_dir.y = ray->player_dir.y + (ray->plane.y * ray->camera_column);
	ray->map_pos.x = (int32_t)ray->player_pos.x;
	ray->map_pos.y = (int32_t)ray->player_pos.y;
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = (double)INFINITY;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = (double)INFINITY;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	update_direction(ray);
	dda_algorithm(ray, cub3d);
	// set_lines
}
