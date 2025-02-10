/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calcs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 20:40:53 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/10 20:43:48 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_wall_textures(t_render *ray, t_cub3d *cub3d)
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

// Calcs the step direction and initial side distances for both axes, based
// on the player_pos and ray_dir. Determines whether the ray is moving up/down
// or left/right and updates the step values.
void	update_direction(t_render *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->map_step.x = -1;
		ray->side_dist.x = (ray->player_pos.x - ray->map_pos.x) * \
							ray->delta_dist.x;
	}
	else
	{
		ray->map_step.x = 1;
		ray->side_dist.x = (ray->player_pos.x + 1.0 - ray->player_pos.x) * \
							ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->map_step.y = -1;
		ray->side_dist.y = (ray->player_pos.y - ray->map_pos.y) * \
							ray->delta_dist.y;
	}
	else
	{
		ray->map_step.y = 1;
		ray->side_dist.y = (ray->player_pos.y + 1.0 - ray->player_pos.y) * \
							ray->delta_dist.y;
	}
}

// Calcs the dist from player to wall, so it can calc the height.
// Also calcs the start and end points of the wall's line.
		// ray->wall_dist = (ray->map_pos.x - ray->player_pos.x + \
		// 				(1.0 - (double)ray->step.x) / 2.0) / ray->ray_dir.x;
		// 
		// ray->wall_dist = (ray->map_pos.y - ray->player_pos.y + \
		// 				(1.0 - (double)ray->step.y) / 2.0) / ray->ray_dir.y;
void	set_wall_height(t_render *ray)
{
	if (ray->side_hit == X_SIDE)
	{
		ray->wall_dist = (ray->side_dist.x - ray->delta_dist.x);
		ray->wall_x = ray->player_pos.y + ray->wall_dist * ray->ray_dir.y;
	}
	else
	{
		ray->wall_dist = (ray->side_dist.y - ray->delta_dist.y);
		ray->wall_x = ray->player_pos.x + ray->wall_dist * ray->ray_dir.x;
	}
	ray->wall_x -= floor(ray->wall_x);
}
