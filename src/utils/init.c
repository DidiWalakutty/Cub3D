/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 20:00:43 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 20:32:53 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// what else can we add to this function?
// t_cub3d	*init_data(void)
// {
// 	t_cub3d	*cub3d;

// 	cub3d = ft_calloc(1, sizeof(t_cub3d));
// 	if (!cub3d)
// 		return (NULL);
// 	// cub3d->ray = ft_calloc(1, sizeof(t_ray));
// 	cub3d->textures = ft_calloc(1, sizeof(t_textures));
// 	if (!cub3d->ray || !cub3d->map || !cub3d->textures)
// 	{
// 		free(cub3d->ray);
// 		free(cub3d->textures);
// 		free(cub3d);
// 		print_error("Couldn't allocate space for struct data");
// 		return (NULL);
// 	}
// 	return (cub3d);
// }

int32_t	get_rgba(int colors[3], int32_t a)
{
	return (colors[0] << 24 | colors[1] << 16 | colors[2] << 8 | a);
}

bool	alloc_execution_structs(t_cub3d *cub3d)
{
	cub3d->textures = malloc(sizeof(t_textures));
	if (!cub3d->textures)
		return (false);
	ft_bzero(cub3d->textures, sizeof(t_textures));
	return (true);
}	