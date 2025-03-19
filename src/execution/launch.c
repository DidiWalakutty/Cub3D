/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:29:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/03/19 14:17:28 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Performs DDA to trace the ray until it hits a wall.
	Steps through the grid one square at a time.
*/
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

/*
	Calcs the ray direction for the current screen column.
	Also does the delta_dist: step size between grid lines.
*/
static void	update_vars(t_render *ray)
{
	ray->map_pos.x = (int)ray->player_pos.x;
	ray->map_pos.y = (int)ray->player_pos.y;
	ray->ray_dir.x = ray->player_dir.x + ray->plane.x * ray->camera_column;
	ray->ray_dir.y = ray->player_dir.y + ray->plane.y * ray->camera_column;
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->ray_dir.y);
}

void	render_minimap(t_cub3d *game)
{
	clear_minimap_image(game);
	draw_minimap_grid(game);
	mlx_image_to_window(game->mlx, game->minimap->minimap_img, 10, 10);
}

/*
	Performs raycasting to render the 3D view by looping
	through each vertical/y screen column.
*/
void	raycaster(void *data)
{
	t_cub3d		*cub3d;
	t_render	*render;
	int			x;

	cub3d = data;
	render = cub3d->render;
	ft_bzero(cub3d->scene->pixels, S_WIDTH * S_HEIGTH * 4);
	x = 0;
	while (x < S_WIDTH)
	{
		render->camera_column = 2 * (x / (double)S_WIDTH) - 1;
		update_vars(render);
		update_side_dist(render);
		dda_algorithm(render, cub3d);
		set_wall_height(render);
		set_wall_textures(render, cub3d);
		draw_wall_slices(cub3d, cub3d->textures, x);
		x++;
	}
	render_minimap(cub3d);
}

void	run_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(S_WIDTH, S_HEIGTH, "Cub3D", false);
	if (!cub3d->mlx)
		end_game(cub3d, "Couldn't init MLX window");
	init_settings(cub3d);
	mlx_loop_hook(cub3d->mlx, keys, cub3d);
	mlx_loop_hook(cub3d->mlx, &raycaster, (void *)cub3d);
	mlx_loop(cub3d->mlx);
	printf("Thank you for playing!\n");
	end_game(cub3d, NULL);
}
