/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:22:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/31 17:30:06 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Update raycast info
void	raycasting(t_render *render)
{

}

// Do we need to reset the image/screen?
void	render(void *data)
{
	t_cub3d		*cub3d;
	mlx_t		*mlx;
	t_render	*render;
	size_t		i;

	cub3d = data;
	mlx = cub3d->mlx;
	render = cub3d->render;
	i = 0;

	while (i < S_WIDTH)
	{
		raycasting(render); // continue here
	}
}
