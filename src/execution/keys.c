// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   keys.c                                             :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2025/01/31 16:27:45 by diwalaku      #+#    #+#                 */
// /*   Updated: 2025/01/31 17:40:47 by diwalaku      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// static void	move_up_down(const t_cub3d *cub3d, char direction)
// {
// 	t_render	*render;
// 	t_dvectr	*update;

// 	render = cub3d->render;
// 	update->x =
// 	update->y =
// }

// static void	move_left_right(const t_cub3d *cub3d, char direction)
// {

// }

// static void turning(const t_cub3d *cub3d, char side)
// {

// }

// // Calculate new player position based on
// // direction and speed.
// void	keys(void *param)
// {
// 	t_cub3d	*cub3d;
// 	mlx_t	*mlx;

// 	cub3d = param;
// 	mlx = cub3d->mlx;

// 	if (mlx_is_key_down(mlx, MLX_KEY_W))
// 		move_up_down(mlx, 'W');
// 	if (mlx_is_key_down(mlx, MLX_KEY_S))
// 		move_up_down(mlx, 'S');
// 	if (mlx_is_key_down(mlx, MLX_KEY_A))
// 		move_left_right(mlx, 'A');
// 	if (mlx_is_key_down(mlx, MLX_KEY_D))
// 		move_left_right(mlx, 'D');
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		turning(mlx, 'L');
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		turning(mlx, 'R');
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 	{
// 		cleanup(cub3d);
// 		mlx_close_window(mlx);
// 		mlx_terminate(mlx); // needed??
// 	}
// }