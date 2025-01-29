/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:29:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 20:50:17 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycaster(t_cub3d *cub3d)
{
	int	x;

	x = 0;
	while (x < S_WIDTH)
	{
			
	}
}

void test()
{
}

// TODO:
// if time: minimap
// raycaster
// MLX hooks and loop
void	run_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(S_WIDTH, S_HEIGTH, "Cub3D", false);	// creates window
	if (!cub3d->mlx)
		end_game(cub3d, "Couldn't init MLX window");
	init_settings(cub3d);
	printf("after init\n");
	// raycaster
	// if time left: mini_map
	mlx_loop_hook(cub3d->mlx, test, NULL);
	mlx_loop(cub3d->mlx);
}

