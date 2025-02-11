/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_moves.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 16:27:45 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/11 15:26:52 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculates the player's new position based on movement direction and speed. 
// If the path is clear, updates the player's position.
static void	move_up_down(const t_cub3d *cub3d, int32_t dir)
{
	t_render	*render;
	t_dvectr	update;

	render = cub3d->render;
	update.x = render->player_pos.x + render->player_dir.x * SPEED * dir;
	update.y = render->player_pos.y + render->player_dir.y * SPEED * dir;
	printf("updated x: %f - y: %f\n", update.x, update.y);
	if (path_clear(cub3d->input->map->grid, cub3d->input->map, update))
	{
		render->player_pos.x = update.x;
		render->player_pos.y = update.y;
		printf("player_posx: %f - player_posy: %f\n", render->player_pos.x, render->player_pos.y);
	}
}

static void	move_left_right(const t_cub3d *cub3d, char dir)
{
	t_render	*render;
	t_dvectr	update;

	render = cub3d->render;
	update.x = render->player_pos.x + render->player_dir.x * SPEED * dir;
	update.y = render->player_pos.y - render->player_dir.y * SPEED * dir;
	if (path_clear(cub3d->input->map->grid, cub3d->input->map, update))
	{
		render->player_pos.x = update.x;
		render->player_pos.y = update.y;
	}
}

static void turning(const t_cub3d *cub3d, char side)
{
	t_dvectr	old_dir;
	double		plane;
	t_render	*render;

	render = cub3d->render;
	old_dir.y = render->player_dir.y;
	render->player_dir.y = render->player_dir.y * cos(ROTATE_S * side) - \
									render->player_dir.x * sin(ROTATE_S * side);
	render->player_dir.x = old_dir.y * sin(ROTATE_S * side) + \
									render->player_dir.x * cos(ROTATE_S * side);
	plane = render->plane.y;
	render->plane.y = render->plane.y * cos(ROTATE_S * side) - \
						render->plane.x * sin(ROTATE_S * side);
	render->plane.x = plane * sin(ROTATE_S * side) + \
						render->plane.x * cos(ROTATE_S * side);
}

// Calculate new player position based on
// direction and speed.
void	keys(void *param)
{
	t_cub3d	*cub3d;
	mlx_t	*mlx;

	cub3d = param;
	mlx = cub3d->mlx;

	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_up_down(cub3d, FORWARD);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_up_down(cub3d, BACKWARDS);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_left_right(cub3d, LEFT);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_left_right(cub3d, RIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		turning(cub3d, TURN_LEFT);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		turning(cub3d, TURN_RIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		cleanup(cub3d);
		mlx_close_window(mlx);
		mlx_terminate(mlx); // needed??
	}
}