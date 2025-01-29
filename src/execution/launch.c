/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:29:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 23:10:18 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(void *data)
{
	t_cub3d	*cub3d;
	// mlx state?
	// all info for map/render/player. What struct?
	size_t	x;

	x = 0;
	while (x < S_WIDTH)
	{
			
	}
}

void keys(void *param)
{
	t_cub3d	*cub3d;
	
	cub3d = param;
	// mlx state
	// if x key is down, move: up, down, left, right.
	// turn and ESC button.
}

// TODO:
// if time: minimap
void	run_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(S_WIDTH, S_HEIGTH, "Cub3D", false);	// creates window
	if (!cub3d->mlx)
		end_game(cub3d, "Couldn't init MLX window");
	init_settings(cub3d);
	// if time left: mini_map
	mlx_loop_hook(cub3d->mlx, keys, cub3d);
	mlx_loop_hook(cub3d->mlx, &render, void(*cub3d));
	// something else?
	mlx_loop(cub3d->mlx);
}

