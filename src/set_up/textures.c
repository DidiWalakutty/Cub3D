/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 20:08:00 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 15:09:04 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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