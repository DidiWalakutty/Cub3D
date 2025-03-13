/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calcs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 20:40:53 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/03/13 15:55:51 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Determines the exact column (x_tex) of the texture to use based on
	wall_heigth. Flips the texture horizontally for certain wall orientations.
*/
static void	place_textures(t_render *ray, t_textures *texture)
{
	texture->x_tex = (int)(ray->wall_heigth * \
							(double)texture->wall_img->width);
	if (ray->side_hit == X_SIDE && ray->ray_dir.x < 0)
		texture->x_tex = texture->wall_img->width - texture->x_tex - 1;
	if (ray->side_hit == Y_SIDE && ray->ray_dir.y < 0)
		texture->x_tex = texture->wall_img->width - texture->x_tex - 1;
}

/*
	Chooses the correct wall texture based on which side of the wall
	was hit (X or Y) and the ray's direction.
*/
void	set_wall_textures(t_render *ray, t_cub3d *cub3d)
{
	t_textures	*texture;

	texture = cub3d->textures;
	if (ray->side_hit == X_SIDE)
	{
		if (ray->ray_dir.x > 0)
			texture->wall_img = texture->east;
		else
			texture->wall_img = texture->west;
	}
	else if (ray->side_hit == Y_SIDE)
	{
		if (ray->ray_dir.y > 0)
			texture->wall_img = texture->south;
		else
			texture->wall_img = texture->north;
	}
	place_textures(ray, texture);
}

/*
	Determines whether the ray steps left/right or up/down.
	Calcs the side_dist (distance to the first grid boundary)
*/
void	update_side_dist(t_render *ray)
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
		ray->side_dist.x = (ray->map_pos.x + 1.0 - ray->player_pos.x) * \
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
		ray->side_dist.y = (ray->map_pos.y + 1.0 - ray->player_pos.y) * \
							ray->delta_dist.y;
	}
}

void	set_wall_height(t_render *ray)
{
	if (ray->side_hit == X_SIDE)
	{
		ray->wall_dist = (ray->side_dist.x - ray->delta_dist.x);
		ray->wall_heigth = ray->player_pos.y + ray->wall_dist * ray->ray_dir.y;
	}
	else
	{
		ray->wall_dist = (ray->side_dist.y - ray->delta_dist.y);
		ray->wall_heigth = ray->player_pos.x + ray->wall_dist * ray->ray_dir.x;
	}
	ray->wall_heigth -= floor((ray->wall_heigth));
}
