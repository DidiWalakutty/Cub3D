/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:29:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/07 21:26:51 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Do we need to reset the image/screen?
static void	raycaster(void *data)
{
	t_cub3d		*cub3d;
	mlx_t		*mlx;
	t_render	*render;
	size_t		screen_col;

	cub3d = data;
	mlx = cub3d->mlx;
	render = cub3d->render;
	// ft_memset(render->scene->pixels, 0, S_WIDTH * S_HEIGTH * sizeof(int32_t));

	screen_col = 0;
	while (screen_col < S_WIDTH)
	{
		create_ray(cub3d, render, screen_col);
		screen_col++;
	}
	// render output
}

void	test()
{

}

// TODO:
// if time: minimap
// raycaster/render
// MLX hooks and loop
void	run_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(S_WIDTH, S_HEIGTH, "Cub3D", false); // creates window
	if (!cub3d->mlx)
		end_game(cub3d, "Couldn't init MLX window");
	init_settings(cub3d, cub3d->input->map->player);
	// if time left: mini_map
	mlx_loop_hook(cub3d->mlx, keys, cub3d);
	mlx_loop_hook(cub3d->mlx, &raycaster, (void*)cub3d);
	// mlx_loop_hook(cub3d->mlx, test, cub3d); // As long as raycaster isn't functioning, use this to test background
	mlx_loop(cub3d->mlx);
}
