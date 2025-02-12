/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 13:49:41 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/12 18:17:25 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	set_n_and_s(t_player *player)
{
	cub3d->scene = mlx_new_image(cub3d->mlx, S_WIDTH, S_HEIGTH);
	cub3d->floor_and_ceiling = mlx_new_image(cub3d->mlx, \
										S_WIDTH, S_HEIGTH);
	if (!cub3d->scene || !cub3d->floor_and_ceiling)
		end_game(cub3d, "Error: Allocation error for image space");
	if (mlx_image_to_window(cub3d->mlx, cub3d->floor_and_ceiling, \
															0, 0) == -1)
		end_game(cub3d, "Error: Couldn't output image to window");
	if (mlx_image_to_window(cub3d->mlx, cub3d->scene, 0, 0) == -1)
		end_game(cub3d, "Error: Couldn't output image to window");
	fill_background(cub3d);
	if (load_wall_textures(cub3d) == false)
		end_game(cub3d, "Error: Couldn't load textures");
}

// Map's origin (0, 0) is top left corner.
// Y is vertical, X is horizontal
// the plane is the camera plane that represents the screen and it always runs
// perpendicular to our direction
static void	set_direction_and_plane(t_player *player)
{
	if (!alloc_execution_structs(cub3d))
		end_game(cub3d, "Error: Couldn't allocate structs");
	initiate_mlx_images(cub3d);
	cub3d->render = set_variables(cub3d);
	if (!cub3d->render)
		end_game(cub3d, "Error: Couldn't alloc render struct");
}

// Need to check which variables we need in here.
// Probably angle, FOV etc as well.
// Need map info for direction.
static void	set_variables(t_cub3d *cub3d)
{
	set_direction_and_plane(cub3d->player); // map info: found letter for direction
	cub3d->player->fov = (FOV * PI) / 180;	// FOV in radians for sin(), cos() and tan().
	// cub3d->player.rotation = 
}
