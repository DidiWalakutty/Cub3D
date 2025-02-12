/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:17:03 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/29 12:23:18 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *errormsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(errormsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void free_grid(char **grid)
{
    int i = 0;
    while (grid[i])
    {
        free(grid[i]);
        i++;
    }
    free(grid);
}

void	cleanup(t_cub3d *game)
{
	if (game->input)
	{
		if (game->input->map)
		{
			if (game->input->map->player)
				free(game->input->map->player);
			if (game->input->map->grid)
                free_grid(game->input->map->grid);
			free(game->input->map);
		}
		free(game->input);
	}
	if (game->map_data)
		free(game->map_data);
	if (game->player)
		free(game->player);
}
