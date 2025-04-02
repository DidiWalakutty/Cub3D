/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 13:49:41 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/04/02 18:48:23 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initiate_mlx_images(t_cub3d *cub3d)
{
	cub3d->scene = mlx_new_image(cub3d->mlx, S_WIDTH, S_HEIGHT);
	cub3d->floor_and_ceiling = mlx_new_image(cub3d->mlx, \
										S_WIDTH, S_HEIGHT);
	cub3d->minimap->minimap_img = mlx_new_image(cub3d->mlx, MINIMAP_WIDTH, \
															MINIMAP_HEIGHT);
	if (!cub3d->scene || !cub3d->floor_and_ceiling || \
		!cub3d->minimap->minimap_img)
		end_game(cub3d, "Allocation error for image space.", true);
	if (mlx_image_to_window(cub3d->mlx, cub3d->floor_and_ceiling, 0, 0) == -1)
		end_game(cub3d, "Couldn't output image to window.", true);
	if (mlx_image_to_window(cub3d->mlx, cub3d->scene, 0, 0) == -1)
		end_game(cub3d, "Couldn't output image to window", true);
	if (mlx_image_to_window(cub3d->mlx, cub3d->minimap->minimap_img, \
							0, 0) == -1)
		end_game(cub3d, "Couldn't output minimap image to window.", true);
	fill_background(cub3d);
	if (load_wall_textures(cub3d) == false)
		end_game(cub3d, "Couldn't load textures.", true);
}

/* 
	mlx_new_image: Creates and allocates a new image buffer.
	mlx_image_to_window: Draws a new instance of an image, 
	it will then share the same pixel buffer as the image. Returns -1 if failed
*/
void	init_settings(t_cub3d *cub3d)
{
	t_render	*temp_render;

	temp_render = cub3d->render;
	if (!alloc_execution_structs(cub3d))
		end_game(cub3d, "Couldn't allocate structs.", true);
	initialize_minimap(cub3d->minimap, cub3d);
	initiate_mlx_images(cub3d);
	cub3d->render = set_variables(cub3d);
	free(temp_render);
	if (!cub3d->render)
		end_game(cub3d, "Couldn't allocate render struct.", true);
}

bool	load_wall_textures(t_cub3d *cub3d)
{
	cub3d->textures->north = mlx_load_png(cub3d->input->north_texture);
	cub3d->textures->south = mlx_load_png(cub3d->input->south_texture);
	cub3d->textures->east = mlx_load_png(cub3d->input->east_texture);
	cub3d->textures->west = mlx_load_png(cub3d->input->west_texture);
	if (!cub3d->textures->north || !cub3d->textures->south || \
		!cub3d->textures->east || !cub3d->textures->west)
		return (false);
	return (true);
}
