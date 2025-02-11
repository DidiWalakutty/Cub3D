/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:22:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/11 14:58:06 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calcs side distances and if the ray hits a wall.
// Determines which direction (x or y) to step in next. 
// Based on which side distance is shorter.
// static void	dda_algorithm(t_render *ray, t_cub3d *cub3d)
// {
// 	while (1)
// 	{
// 		if (ray->side_dist.x < ray->side_dist.y)
// 		{
// 			ray->side_dist.x += ray->delta_dist.x;
// 			ray->map_pos.x += ray->map_step.x;
// 			ray->side_hit = X_SIDE;
// 		}
// 		else
// 		{
// 			ray->side_dist.y += ray->delta_dist.y;
// 			ray->map_pos.y += ray->map_step.y;
// 			ray->side_hit = Y_SIDE;
// 		}
// 		if (cub3d->input->map->grid[ray->map_pos.y][ray->map_pos.x] == '1')
// 			break ;
// 		// if (hit_wall(cub3d->input->map->grid, ray->map_pos.y, ray->map_pos.x))
// 	}
// }

void	draw_line_loops(t_cub3d *cub3d, t_textures *text, int x)
{
	long		draw_start;
	long		draw_end;
	int			lineheigth;
	uint32_t	color;
	t_render	*r;

	r = cub3d->render;
	lineheigth = (int)S_HEIGTH / r->wall_dist;
	draw_start = -lineheigth / 2 + (S_HEIGTH / 2);
	draw_end = lineheigth / 2 + (S_HEIGTH /2);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= S_HEIGTH)
		draw_end = S_HEIGTH - 1;
	text->pix_step = (1.0 * text->wall_img->height / lineheigth);
	text->tex_pos = (draw_start - (S_HEIGTH / 2) + (lineheigth / 2)) * text->pix_step;
	while (draw_start < draw_end && draw_start < S_HEIGTH)
	{
		text->y_tex = (int)text->tex_pos & (text->wall_img->height - 1);
		text->tex_pos += text->pix_step;
		color = color_texture(text, text->x_tex, text->y_tex);
		mlx_put_pixel(cub3d->scene, x, draw_start, color);
		// mlx_put_pixel(cub3d->scene, x, draw_start, 0x000000ff);
		draw_start++;
	}
}
