/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 20:00:43 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/03/13 16:01:38 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	alloc_execution_structs(t_cub3d *cub3d)
{
	cub3d->textures = malloc(sizeof(t_textures));
	if (!cub3d->textures)
		return (false);
	ft_bzero(cub3d->textures, sizeof(t_textures));
	cub3d->minimap = malloc(sizeof(t_minimap));
	if (!cub3d->minimap)
		return (false);
	ft_bzero(cub3d->minimap, sizeof(t_minimap));
	return (true);
}

void	initialize_minimap(t_minimap *minimap, t_cub3d *game)
{
	minimap->w = MINIMAP_WIDTH;
	minimap->h = MINIMAP_HEIGHT;
	minimap->scale = fmin ((double) MINIMAP_WIDTH / game->input->map->width, \
						(double) MINIMAP_HEIGHT / game->input->map->height);
	minimap->player_color = PLAYER_COLOR;
	minimap->wall_color = WALL_COLOR;
	minimap->floor_color = FLOOR_COLOR;
}
