/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:22:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/09 14:06:29 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calcs the step direction and initial side distances for both axes, based
// on the player_pos and ray_dir. Determines whether the ray is moving up/down
// or left/right and updates the step values.
static void	update_direction(t_render *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->player_pos.x - ray->map_pos.x) * \
							ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->player_pos.x + 1.0 - ray->player_pos.x) * \
							ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->player_pos.y - ray->map_pos.y) * \
							ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->player_pos.y + 1.0 - ray->player_pos.y) * \
							ray->delta_dist.y;
	}
}

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
			ray->map_pos.x += ray->step.x;
			ray->wall_hit = X_SIDE;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->wall_hit = Y_SIDE;
		}
		if (hit_wall(cub3d->input->map->grid, ray->map_pos.y, ray->map_pos.x))
			break ;
	}
}

// Calcs the dist from player to wall, so it can calc the height.
// Also calcs the start and end points of the wall's line.
		// ray->wall_dist = (ray->map_pos.x - ray->player_pos.x + \
		// 				(1.0 - (double)ray->step.x) / 2.0) / ray->ray_dir.x;
		// 
		// ray->wall_dist = (ray->map_pos.y - ray->player_pos.y + \
		// 				(1.0 - (double)ray->step.y) / 2.0) / ray->ray_dir.y;
static void	set_wall_height(t_render *ray)
{
	if (ray->wall_hit == X_SIDE)
		ray->wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->wall_dist = (ray->side_dist.y - ray->delta_dist.y);
	if (ray->wall_dist == 0)
		ray->line.height = S_HEIGTH;
	else
		ray->line.height = (int)(S_HEIGTH / ray->wall_dist);
	ray->line.start = (S_HEIGTH / 2) - (ray->line.height / 2);
	if (ray->line.start < 0)
		ray->line.start = 0;
	ray->line.end = (S_HEIGTH / 2) + (ray->line.height / 2);
	if (ray->line.end >= S_HEIGTH)
		ray->line.end = S_HEIGTH - 1;
}

// tex_col determines which column of the texture should be used
// for this wall slice.
// X_SIDE = 0 = vertical wall N/S
// Y_SIDE = 1 = horizontal wall E/W
static void	set_wall_textures(t_render *ray, t_cub3d *cub3d)
{
	// mlx_texture_t	*tex_img;
	t_textures		*text;
	// int				y;

	text = cub3d->textures;
	// segfaults, text is empty
	if (ray->wall_hit == X_SIDE)
	{
		if (ray->ray_dir.y > 0)
			cub3d->textures->wall_img = cub3d->textures->north;
		else
			cub3d->textures->wall_img = cub3d->textures->south;
	}
	else if (ray->wall_hit == Y_SIDE)
	{
		if (ray->ray_dir.x > 0)
			cub3d->textures->wall_img = cub3d->textures->west;
		else
			cub3d->textures->wall_img = cub3d->textures->east;
	}
	// removes integer parts, keeps fractional part
	// because it tells us where within a single wall block we hit
	// text->wall_x_pos -= floor(text->wall_x_pos);
	// calcs which vertical strip of texture we need to use
	text->x_tex = (int)(text->wall_x_pos * (double)text->wall_img->width);
	// flips texture, because of mirroring
	if (ray->wall_hit == X_SIDE && ray->ray_dir.x > 0)
		text->x_tex = text->wall_img->width - text->x_tex - 1;
	if (ray->wall_hit == Y_SIDE && ray->ray_dir.y < 0)
		text->x_tex = text->wall_img->width - text->x_tex - 1;
	text->pix_step = 1.0 * text->wall_img->height / ray->line.height;	// double check height of this
	text->tex_pos = (ray->line.start - S_HEIGTH / 2 + ray->line.height) * text->pix_step;
	fill_background(cub3d);	// use here??
	loop_screenpixels(ray, text, text->wall_img);
}

// Generates a new ray.
// Calcs the camera coordinate, updates ray direction and sets pos in map.
// Calcs the delta distance (how much a ray moves in each step) for x and y.
void	create_ray(t_cub3d *cub3d, t_render *ray, size_t screen_i)
{
	ray->camera_column = 2 * ((double)screen_i / (double)S_WIDTH) - 1;
	ray->ray_dir.x = ray->player_dir.x + (ray->plane.x * ray->camera_column);
	ray->ray_dir.y = ray->player_dir.y + (ray->plane.y * ray->camera_column);
	ray->map_pos.x = (int32_t)ray->player_pos.x;
	ray->map_pos.y = (int32_t)ray->player_pos.y;
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
	set_wall_textures(ray, cub3d); // cub3d needed?
}
