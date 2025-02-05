/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 16:27:45 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/04 15:38:18 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// player_dir.x/y = how much the player moves
// * speed the player moves * direction (forward or backwards)
// player_pos.x/y: above is added to this amount to get new pos.
static void	move_up_down(const t_cub3d *cub3d, int32_t dir)
{
	t_render	*render;
	t_dvectr	update;

	render = cub3d->render;
	update->x = render->player_pos.x + render->player_direction.x * SPEED * dir; 
	update->y = render->player_pos.y + render->player_direction.y * SPEED * dir;
	// check if new row is valid
	if (path_clear(cub3d->map.grid, render.player_pos, update, cub3d.player_dir))
	{
		cub3d.player_pos.x = update.x;
		cub3d.player_pos.y = update.y;
	}
}

static void	move_left_right(const t_cub3d *cub3d, char dir)
{

}

static void turning(const t_cub3d *cub3d, char side)
{

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
		move_up_down(mlx, FORWARD);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_up_down(mlx, BACKWARDS);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_left_right(mlx, LEFT);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_left_right(mlx, RIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		turning(mlx, TURN_LEFT);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		turning(mlx, TURN_RIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		cleanup(cub3d);
		mlx_close_window(mlx);
		mlx_terminate(mlx); // needed??
	}
}