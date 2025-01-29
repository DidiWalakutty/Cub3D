/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:17:14 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/29 11:50:59 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		printf("fail\n");
		cleanup(&game);
		return (1);
	}
	// adjust game struct pointers
	print_map(game.input->map->grid);
	cleanup(&game); // temporary cleanup
	return (0);
}
