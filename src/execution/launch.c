/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:29:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/12 18:43:46 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Performs DDA to trace the ray until it hits a wall.
// Steps through the grid one square at a time.
static void	dda_algorithm(t_render *ray, t_cub3d *cub3d)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->map_step.x;
			ray->side_hit = X_SIDE;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->map_step.y;
			ray->side_hit = Y_SIDE;
		}
		if (cub3d->input->map->grid[ray->map_pos.y][ray->map_pos.x] == '1')
			break ;
	}
}

// Calcs the ray direction for the current screen column.
// Also does the delta_dist: step size between grid lines.
static void	update_vars(t_cub3d *cub3d, t_render *ray)
{
	ray->map_pos.x = (int)ray->player_pos.x;
	ray->map_pos.y = (int)ray->player_pos.y;
	ray->ray_dir.x = ray->player_dir.x + ray->plane.x * ray->camera_column;
	ray->ray_dir.y = ray->player_dir.y + ray->plane.y * ray->camera_column;
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs((float)1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs((float)1 / ray->ray_dir.y);
}

// Performs raycasting to render the 3D view by looping
// through each vertical/y screen column.
static void	raycaster(void *data)
{
	t_cub3d		*cub3d;
	t_render	*render;
	int			y;

	cub3d = data;
	render = cub3d->render;
	ft_bzero(cub3d->scene->pixels, S_WIDTH * S_HEIGTH * 4);
	y = 0;
	while (y < S_WIDTH)
	{
		render->camera_column = 2 * (y / (double)S_WIDTH) - 1;
		update_vars(cub3d, render);
		update_side_dist(render);
		dda_algorithm(render, cub3d);
		set_wall_height(render);
		// Stretched texture is probably in set_wall_textures,  
		// place_textures (in set_text) or draw_wall_slices.
		set_wall_textures(render, cub3d);
		draw_wall_slices(cub3d, cub3d->textures, y);
		y++;
	}
}

// TODO:
// if time: minimap
void	run_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(S_WIDTH, S_HEIGTH, "Cub3D", false);
	if (!cub3d->mlx)
		end_game(cub3d, "Error: Couldn't init MLX window");
	init_settings(cub3d);
	// mini_map
	mlx_loop_hook(cub3d->mlx, keys, cub3d);
	mlx_loop_hook(cub3d->mlx, &raycaster, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
