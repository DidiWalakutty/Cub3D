/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:22:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/10 21:40:57 by diwalaku      ########   odam.nl         */
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
		// if (hit_wall(cub3d->input->map->grid, ray->map_pos.y, ray->map_pos.x)) // in case hit wall sucks agian
	}
}

// tex_col determines which column of the texture should be used
// for this wall slice.
// X_SIDE = 0 = vertical wall N/S
// Y_SIDE = 1 = horizontal wall E/W
static void	set_wall_textures(t_render *ray, t_cub3d *cub3d)
{
	t_textures	*texture;

	texture = cub3d->textures;
	if (ray->side_hit == X_SIDE)
	{
		if (ray->ray_dir.y > 0)
			texture->wall_img = texture->north;
		else
			texture->wall_img = texture->south;
	}
	else if (ray->side_hit == Y_SIDE)
	{
		if (ray->ray_dir.x > 0)
			texture->wall_img = texture->west;
		else
			texture->wall_img = texture->east;
	}
	// removes integer parts, keeps fractional part
	// because it tells us where within a single wall block we hit
	// text->wall_x_pos -= floor(text->wall_x_pos);
	// calcs which vertical strip of texture we need to use
	texture->x_tex = (int)(texture->wall_x_pos \
							* (double)texture->wall_img->width);
	// flips texture, because of mirroring
	if (ray->side_hit == X_SIDE && ray->ray_dir.x > 0)
		texture->x_tex = texture->wall_img->width - texture->x_tex - 1;
	if (ray->side_hit == Y_SIDE && ray->ray_dir.y < 0)
		texture->x_tex = texture->wall_img->width - texture->x_tex - 1;
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
	// color = color_texture(text, text->x_tex, text->y_tex);
	while (draw_start < draw_end && draw_start < S_HEIGTH)
	{
		text->y_tex = (int)text->tex_pos & (text->wall_img->height - 1);
		text->tex_pos += text->pix_step;
		color = color_texture(text, text->x_tex, text->y_tex);
		mlx_put_pixel(cub3d->scene, x, draw_start, 0x000000ff);
		draw_start++;
	}
	// int y = S_HEIGTH / 2;
	// int n;
	// while (y < S_HEIGTH - 1)
	// {
	// 	// n = 0;
	// 	// while(n < S_WIDTH - 1)
	// 	// {
	// 		mlx_put_pixel(cub3d->scene, y, 0, 35);
	// 		// n++;
	// 	// }
	// 	y++;
	// }
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
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = (double)INFINITY;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	update_direction(ray);
	dda_algorithm(ray, cub3d);
	set_wall_height(ray);
	set_wall_textures(ray, cub3d);
	draw_calculations(ray, cub3d);
	draw_line_loops(cub3d, cub3d->textures, x);
}
