/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:22:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/12 18:50:20 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Draws each vertical line (wall slice)
// pix_step: how much to move through the texture for each vertical pixel
// tex_pos: starts at the correct position within the texture for the first
// pixel of the wa;l.
// y_tex: calcs the correct texture coordinate for the vertical pixel.
void	draw_wall_slices(t_cub3d *cub3d, t_textures *text, int x)
{
	long		draw_start;
	long		draw_end;
	int			lineheigth;
	uint32_t	color;
	t_render	*r;

	r = cub3d->render;
	lineheigth = (int)S_HEIGTH / r->wall_dist;
	draw_start = -lineheigth / 2 + (S_HEIGTH / 2);
	draw_end = lineheigth / 2 + (S_HEIGTH / 2);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= S_HEIGTH)
		draw_end = S_HEIGTH - 1;
	// Stretched texture issue could also be pix_step and/or tex_pos
	text->pix_step = (1.0 * text->wall_img->height / lineheigth);
	text->tex_pos = (draw_start - (S_HEIGTH / 2) + (lineheigth / 2)) * \
					text->pix_step;
	while (draw_start < draw_end && draw_start < S_HEIGTH)
	{
		text->y_tex = (int)text->tex_pos & (text->wall_img->height - 1);
		text->tex_pos += text->pix_step;
		color = color_texture(text, text->x_tex, text->y_tex);
		mlx_put_pixel(cub3d->scene, x, draw_start, color);
		draw_start++;
	}
}
