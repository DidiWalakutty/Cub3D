/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:29:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/11 14:29:09 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Do we need to reset the image/screen?
static void	raycaster(void *data)
{
	t_cub3d		*cub3d;
	t_render	*render;
	int			y;

	cub3d = data;
	render = cub3d->render;
	ft_memset(cub3d->scene->pixels, 0xFF000000, S_WIDTH * S_HEIGTH * sizeof(uint32_t));
	y = 0;
	while (y < S_WIDTH)
	{
		create_ray(cub3d, render, y);
		y++;
	}
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
	init_settings(cub3d);
	// if time left: mini_map
	mlx_loop_hook(cub3d->mlx, keys, cub3d);
	mlx_loop_hook(cub3d->mlx, &raycaster, (void*)cub3d);
	// mlx_loop_hook(cub3d->mlx, test, cub3d); // As long as raycaster isn't functioning, use this to test background
	mlx_loop(cub3d->mlx);
}
