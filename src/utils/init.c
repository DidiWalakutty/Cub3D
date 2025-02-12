/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 20:00:43 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/31 17:29:01 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	alloc_execution_structs(t_cub3d *cub3d)
{
	cub3d->textures = malloc(sizeof(t_textures));
	if (!cub3d->textures)
		return (false);
	cub3d->render = malloc(sizeof(t_render));
	if (!cub3d->render)
		return (false);
	ft_bzero(cub3d->textures, sizeof(t_textures));
	ft_bzero(cub3d->render, sizeof (t_render));
	return (true);
}
