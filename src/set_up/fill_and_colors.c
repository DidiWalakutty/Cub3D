/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_and_colors.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 20:08:00 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/07 21:16:56 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int32_t	get_array_rgb(int colors[3], int32_t a)
{
	return (colors[0] << 24 | colors[1] << 16 | colors[2] << 8 | a);
}

void	fill_background(t_cub3d *cub3d)
{
	cub3d->textures->ceiling_color = get_array_rgb(cub3d->input->ceiling_colors, 255);
	cub3d->textures->floor_color = get_array_rgb(cub3d->input->floor_colors, 255);
	draw_background(cub3d);
}

static uint32_t	color_texture(t_textures *text, double x_info, double y_info)
{
	uint8_t	*pixels;
	int		x;
	int		y;
	int		index;

	x = (int)x_info;
	y = (int)y_info;
	index = (y * text->wall_img->width + x) * text->wall_img->bytes_per_pixel;
	pixels = text->wall_img->pixels;
	text->r = pixels[index];
	text->g = pixels[index + 1];
	text->b = pixels[index + 2];
	text->a = pixels[index + 3];
	return ((uint32_t)(text->r << 24 | text->g << 16 | text->b << 8 | text->a));
}

void	loop_screenpixels(t_render *ray, t_textures	*text, mlx_texture_t *wall)
{
	int32_t		draw_start;
	int32_t		draw_end;
	uint32_t	color;
	int			i;

	draw_start = ray->line.start;
	draw_end = ray->line.end;
	i = 0;
	// while (draw_start < draw_end && draw_start < S_HEIGTH)
	while (i < draw_end)
	{
		text->y_tex = (int)text->tex_pos & (wall->height - 1);
		text->tex_pos += text->pix_step;
		color = color_texture(text, text->x_tex, text->y_tex);
		mlx_put_pixel(ray->scene, i, ray->line.start, color);
		i++;
	}
}
