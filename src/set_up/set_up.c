/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 13:49:41 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 20:51:56 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	set_n_and_s(t_player *player)
{
	if (player->orientation == 'N')
	{
		player->direction.x = 0;
		player->direction.y = -1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
	else
	{
		player->direction.x = 0;
		player->direction.y = 1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
}

// Map's origin (0, 0) is top left corner.
// Y is vertical, X is horizontal
// the plane is the camera plane that represents the screen and it always runs
// perpendicular to our direction
static void	set_direction_and_plane(t_player *player)
{
	if (player->orientation == 'N' || player->orientation == 'S')
		set_n_and_s(player);
	else if (player->orientation == 'E')
	{
		player->direction.x = 1;
		player->direction.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
	else if (player->orientation == 'W')
	{
		player->direction.x = -1;
		player->direction.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	player->position.x = (double)player->x; // + 0.5 so in middle of tile?
	player->position.y = (double)player->y;
}

// Need to check which variables we need in here.
// Probably angle, FOV etc as well.
// Need map info for direction.
static void	set_variables(t_cub3d *cub3d)
{
	printf("in set variables\n");
	set_direction_and_plane(cub3d->player);
	printf("after setting direction and plane\n");
	cub3d->player->fov = (FOV * PI) / 180;	// FOV in radians
	// cub3d->player.rotation = 
}





// mlx_new_image: Creates and allocates a new image buffer.
// mlx_image_to_window: Draws a new instance of an image, 
// it will then share the same pixel buffer as the image. Returns -1 if failed
void	init_settings(t_cub3d *cub3d)
{
	if (!alloc_execution_structs(cub3d))
		end_game(cub3d, "Couldn't allocate structs");
	// cub3d->render.wall = mlx_new_image(cub3d->mlx, S_WIDTH, S_HEIGTH);
	cub3d->render.floor_and_ceiling = mlx_new_image(cub3d->mlx, \
													S_WIDTH, S_HEIGTH);
	// if (!cub3d->render.wall || !cub3d->render.floor_and_ceiling)
		// end_game(cub3d, "Allocation error for image space");
	// if (mlx_image_to_window(cub3d->mlx, cub3d->render.wall, 0, 0) == -1)
	// 	end_game(cub3d, "Couldn't output image to window");
	if (mlx_image_to_window(cub3d->mlx, cub3d->render.floor_and_ceiling, \
															0, 0) == -1)
		end_game(cub3d, "Couldn't output image to window");
	fill_background(cub3d);
	// if (load_wall_textures(cub3d) == false)									// loads wall images
	// 	end_game(cub3d, "Couldn't load textures");
	// set_variables(cub3d);
}
