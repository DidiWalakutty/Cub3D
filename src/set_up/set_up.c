/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 13:49:41 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 15:47:33 by diwalaku      ########   odam.nl         */
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
	player->position.x = (double)player->x;
	player->position.y = (double)player->y;
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

// scene is pointer to the pixel array.
static void	fill_background(void *scene, int ceiling_color, int floor_color, \
			size_t total_pixels)
{
	size_t	i;
	int		*image;

	image = (int *)scene;
	i = 0;
	while (i < S_UPPER_HALF)
	{
		image[i] = ceiling_color;
		i++;
	}
	while (i < total_pixels)
	{
		image[i] = floor_color;
		i++;
	}
}

// mlx_new_image: Creates and allocates a new image buffer.
// mlx_image_to_window: Draws a new instance of an image, 
// it will then share the same pixel buffer as the image. Returns -1 if failed
// Choose colors for ceiling and floor!
void	set_mlx_and_variables(t_cub3d *cub3d)
{
	cub3d->textures->floor_color = rgba_to_int(cub3d->input->ceiling_colors, 255);
	cub3d->textures->ceiling_color = rgba_to_int(cub3d->input->floor_colors, 255);

	cub3d->render.wall = mlx_new_image(cub3d->mlx, S_WIDTH, S_HEIGTH);
	cub3d->render.floor_and_ceiling = mlx_new_image(cub3d->mlx, \
													S_WIDTH, S_HEIGTH);
	if (!cub3d->render.wall || !cub3d->render.floor_and_ceiling)
		end_game(cub3d, "Allocation error for image space");
	if (mlx_image_to_window(cub3d->mlx, cub3d->render.wall, 0, 0) == -1)
		end_game(cub3d, "Couldn't output image to window");
	if (mlx_image_to_window(cub3d->mlx, cub3d->render.floor_and_ceiling, 0, 0) == -1)
		end_game(cub3d, "Couldn't output image to window");
	fill_background(cub3d->render.floor_and_ceiling->pixels, \
	cub3d->textures->ceiling_color, cub3d->textures->floor_color, \
					S_UPPER_HALF + S_LOWER_HALF);
	set_variables(cub3d);
}
