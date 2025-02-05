/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_and_colors.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 20:08:00 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/05 14:43:15 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	load_wall_textures(t_cub3d *cub3d)
{
	// xmp_t
	cub3d->textures->north = mlx_load_png(cub3d->input->north_texture);
	cub3d->textures->south = mlx_load_png(cub3d->input->south_texture);
	cub3d->textures->east = mlx_load_png(cub3d->input->east_texture);
	cub3d->textures->west = mlx_load_png(cub3d->input->west_texture);
	if (!cub3d->textures->north || !cub3d->textures->south || \
		!cub3d->textures->east || !cub3d->textures->west)
		return (false);
	return (true);
}

static void	draw_background(t_cub3d *cub3d)
{
	mlx_image_t	*mlx_img;
	int			x;
	int			y;

	x = 0;
	mlx_img = cub3d->render->floor_and_ceiling;
	while (x < S_WIDTH)
	{
		y = 0;
		while (y < S_HEIGTH)
		{
			if (y < (S_HEIGTH / 2))
				mlx_put_pixel(mlx_img, x, y, cub3d->textures->ceiling_color);
			else
				mlx_put_pixel(mlx_img, x, y, cub3d->textures->floor_color);
			y++;
		}
		x++;
	}
}

static int32_t	get_rgb(int colors[3], int32_t a)
{
	return (colors[0] << 24 | colors[1] << 16 | colors[2] << 8 | a);
}

void	fill_background(t_cub3d *cub3d)
{
	cub3d->textures->ceiling_color = get_rgb(cub3d->input->ceiling_colors, 255);
	cub3d->textures->floor_color = get_rgb(cub3d->input->floor_colors, 255);
	draw_background(cub3d);
}
