/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 13:49:41 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/20 16:53:24 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initiate_mlx_images(t_cub3d *cub3d)
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

/* mlx_new_image: Creates and allocates a new image buffer.
mlx_image_to_window: Draws a new instance of an image, 
it will then share the same pixel buffer as the image. Returns -1 if failed
*/
void	init_settings(t_cub3d *cub3d)
{
	t_render	*temp_render;

	temp_render = cub3d->render;
	if (!alloc_execution_structs(cub3d))
		end_game(cub3d, "Error: Couldn't allocate structs");
	initiate_mlx_images(cub3d);
	cub3d->render = set_variables(cub3d);
	free(temp_render);
	if (!cub3d->render)
		end_game(cub3d, "Error: Couldn't alloc render struct");
}

bool	load_wall_textures(t_cub3d *cub3d)
{
	cub3d->textures->north = mlx_load_png("textures/Space_N.png");
	cub3d->textures->south = mlx_load_png("textures/Space_S.png");
	cub3d->textures->east = mlx_load_png("textures/Space_E.png");
	cub3d->textures->west = mlx_load_png("textures/Space_W.png");
	if (!cub3d->textures->north || !cub3d->textures->south || \
		!cub3d->textures->east || !cub3d->textures->west)
		return (false);
	return (true);
}
