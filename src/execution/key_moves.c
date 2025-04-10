/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_moves.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 16:27:45 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/03/27 16:00:43 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Calculates the player's new position based on movement direction and speed.
	If the path is clear, updates the player's position.
*/
static void	move_up_down(const t_cub3d *cub3d, int32_t dir)
{
	t_render	*render;
	t_dvectr	update;

	render = cub3d->render;
	update.x = render->player_pos.x + render->player_dir.x * SPEED * dir;
	update.y = render->player_pos.y + render->player_dir.y * SPEED * dir;
	if (path_clear(cub3d->input->map->grid, cub3d->input->map, update))
	{
		render->player_pos.x = update.x;
		render->player_pos.y = update.y;
	}
}

/*
	Moves player sideways by shifting movement 90 degrees.
*/
static void	move_left_right(const t_cub3d *cub3d, int32_t dir)
{
	t_render	*render;
	t_dvectr	update;

	render = cub3d->render;
	update.x = render->player_pos.x + render->player_dir.y * SPEED * dir;
	update.y = render->player_pos.y - render->player_dir.x * SPEED * dir;
	if (path_clear(cub3d->input->map->grid, cub3d->input->map, update))
	{
		render->player_pos.x = update.x;
		render->player_pos.y = update.y;
	}
}

/*
	Uses 2D rotation formulas using a standard rotation matrix 
	to update the player_dir and plane (fov).
	If wall_dist is less than 0.5, we increase the speed.
*/
static void	turning(const t_cub3d *cub3d, double rotspeed)
{
	t_dvectr	*dir;
	double		old_dir_x;
	double		old_plane_x;
	t_dvectr	*plane;
	double		adjusted_rotspeed;

	dir = &cub3d->render->player_dir;
	plane = &cub3d->render->plane;
	old_dir_x = dir->x;
	old_plane_x = plane->x;
	if (cub3d->render->wall_dist < 0.5)
		adjusted_rotspeed = rotspeed * 1.6;
	else
		adjusted_rotspeed = rotspeed;
	dir->x = dir->x * cos(adjusted_rotspeed) - dir->y * sin(adjusted_rotspeed);
	dir->y = old_dir_x * sin(adjusted_rotspeed) + dir->y * \
							cos(adjusted_rotspeed);
	plane->x = plane->x * cos(adjusted_rotspeed) - plane->y * \
							sin(adjusted_rotspeed);
	plane->y = old_plane_x * sin(adjusted_rotspeed) + plane->y * \
							cos(adjusted_rotspeed);
}

void	keys(void *param)
{
	t_cub3d	*cub3d;
	mlx_t	*mlx;
	double	rotspeed;

	cub3d = param;
	mlx = cub3d->mlx;
	rotspeed = 0.023 * 1.4;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_up_down(cub3d, FORWARD);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_up_down(cub3d, BACKWARDS);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_left_right(cub3d, LEFT);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_left_right(cub3d, RIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		turning(cub3d, -rotspeed);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		turning(cub3d, rotspeed);
}
