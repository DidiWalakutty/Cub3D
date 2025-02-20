/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 20:00:43 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/20 16:53:44 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	alloc_execution_structs(t_cub3d *cub3d)
{
	cub3d->textures = malloc(sizeof(t_textures));
	if (!cub3d->textures)
		return (false);
	ft_bzero(cub3d->textures, sizeof(t_textures));
	return (true);
}
