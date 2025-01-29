/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 19:29:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 15:09:40 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_environment(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < S_HEIGTH)
	{
		x = 0;
		while (x < S_WIDTH)
		{
			
		}
	}
}

// TODO:
// set colors and walls
// if time: minimap
// raycaster
// MLX hooks and loop
void	run_cub3d(t_cub3d *cub3d)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1); 		// does resizing of window
	cub3d->mlx = mlx_init(S_WIDTH, S_HEIGTH, "Cub3D", true);	// creates window
	if (!cub3d->mlx)
		end_game(cub3d, "Couldn't init MLX window");
	set_mlx_and_variables(cub3d);				// sets floor + ceiling
	// TODO:
	if (load_wall_textures(cub3d) == false)
		end_game(cub3d, "Couldn't load textures");
	draw_environment(cub3d);
	// raycaster
	// if time left: mini_map
	// mlx hooks
	// mlx_loop
	
}

