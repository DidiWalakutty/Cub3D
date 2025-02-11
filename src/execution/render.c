/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:22:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/11 14:24:32 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calcs side distances and if the ray hits a wall.
// Determines which direction (x or y) to step in next. 
// Based on which side distance is shorter.
static void	dda_algorithm(t_render *ray, t_cub3d *cub3d)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->map_step.x;
			ray->side_hit = X_SIDE;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->map_step.y;
			ray->side_hit = Y_SIDE;
		}
		if (cub3d->input->map->grid[ray->map_pos.y][ray->map_pos.x] == '1')
			break ;
		// if (hit_wall(cub3d->input->map->grid, ray->map_pos.y, ray->map_pos.x))
	}
}

void	draw_line_loops(t_cub3d *cub3d, t_textures *text, int x)
{
	int32_t		draw_start;
	int32_t		draw_end;
	uint32_t	color;
	t_render	*r;

	r = cub3d->render;
	draw_start = r->line.start;
	draw_end = r->line.end;
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

// Generates a new ray.
// Calcs the camera coordinate, updates ray direction and sets pos in map.
// Calcs the delta distance (how much a ray moves in each step) for x and y.
void	create_ray(t_cub3d *cub3d, t_render *ray, int x)
{
	ray->camera_column = 2 * (x / (double)S_WIDTH) - 1;
	ray->map_pos.x = (int32_t)ray->player_pos.x;
	ray->map_pos.y = (int32_t)ray->player_pos.y;
	ray->ray_dir.x = ray->player_dir.x + (ray->plane.x * ray->camera_column);
	ray->ray_dir.y = ray->player_dir.y + (ray->plane.y * ray->camera_column);
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = (double)INFINITY;
	else
		ray->delta_dist.x = fabs((float)1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = (double)INFINITY;
	else
		ray->delta_dist.y = fabs((float)1 / ray->ray_dir.y);
	update_side_dist(ray);
	dda_algorithm(ray, cub3d);
	set_wall_height(ray);
	set_wall_textures(ray, cub3d);
	draw_calculations(ray, cub3d);
	draw_line_loops(cub3d, cub3d->textures, x);
}
