/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_and_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:08:00 by diwalaku          #+#    #+#             */
/*   Updated: 2025/02/14 13:51:25 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_cub3d *cub3d)
{
	mlx_image_t	*mlx_img;
	int			x;
	int			y;

	x = 0;
	mlx_img = cub3d->floor_and_ceiling;
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

static uint32_t	get_rrgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	color_texture(t_textures *text, double x_info, double y_info)
{
	uint8_t	*pixels;
	int		x;
	int		y;
	int		index;
	//printf("x_info: %f\n", x_info);
	//printf("y_info: %f\n", y_info);

	x = (int)x_info;
	y = (int)y_info;
	index = (y * text->wall_img->width + x) * text->wall_img->bytes_per_pixel;
	pixels = text->wall_img->pixels;
	text->r = pixels[index];
	text->g = pixels[index + 1];
	text->b = pixels[index + 2];
	text->a = pixels[index + 3];
	return (get_rrgba(text->r, text->g, text->b, text->a));
}
