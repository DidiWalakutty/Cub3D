/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:17:03 by ykarimi           #+#    #+#             */
/*   Updated: 2025/04/06 13:50:20 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *errormsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(errormsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	free_mlx_data(t_cub3d *cub3d)
{
	if (cub3d->floor_and_ceiling)
		mlx_delete_image(cub3d->mlx, cub3d->floor_and_ceiling);
	if (cub3d->scene)
		mlx_delete_image(cub3d->mlx, cub3d->scene);
	if (cub3d->textures->north)
		mlx_delete_texture(cub3d->textures->north);
	if (cub3d->textures->east)
		mlx_delete_texture(cub3d->textures->east);
	if (cub3d->textures->south)
		mlx_delete_texture(cub3d->textures->south);
	if (cub3d->textures->west)
		mlx_delete_texture(cub3d->textures->west);
	if (cub3d->textures)
		free(cub3d->textures);
	if (cub3d->minimap && cub3d->minimap->minimap_img)
		mlx_delete_image(cub3d->mlx, cub3d->minimap->minimap_img);
	if (cub3d->minimap)
		free(cub3d->minimap);
}

void	cleanup(t_cub3d *game)
{
	if (game->input)
	{
		if (game->input->map)
		{
			if (game->input->map->grid)
				free_grid(game->input->map->grid);
			if (game->input->map->player)
				free(game->input->map->player);
			free(game->input->map);
		}
		free(game->input->north_texture);
		free(game->input->south_texture);
		free(game->input->east_texture);
		free(game->input->west_texture);
		free(game->input);
	}
	if (game->render)
		free(game->render);
}

// add third arg if end_game isnt failure
void	end_game(t_cub3d *game, char *message, bool failure)
{
	if (message)
		print_error(message);
	if (game == NULL)
		return ;
	cleanup(game);
	if (game->mlx)
	{
		free_mlx_data(game);
		mlx_terminate(game->mlx);
	}
	if (failure)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
