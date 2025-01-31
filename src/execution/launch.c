/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:29:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/31 17:26:12 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_loop_hook(cub3d->mlx, keys, cub3d); // continu with keys after raycasting is up and running
	mlx_loop_hook(cub3d->mlx, &render, cub3d);
	mlx_loop(cub3d->mlx);
}
