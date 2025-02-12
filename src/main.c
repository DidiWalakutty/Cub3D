/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:17:14 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/02/12 18:01:17 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub3d	game;

	if (argc != 2)
		return (print_error("Too many or few arguments provided"), 1);
	ft_bzero(&game, sizeof(t_cub3d));
	game.input = malloc(sizeof(t_input));
	if (!game.input)
		return (print_error("memory allocation for input failed."), 1);
	ft_bzero(game.input, sizeof(t_input));
	if (parse_file(argv, game.input) == 1)
	{
		cleanup(&game);
		return (1);
	}
	print_map(game.input->map->grid);
	run_cub3d(&game);
	end_game(&game, "Thanks for playing");
	return (0);
}
