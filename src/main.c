/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:17:14 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/01/28 12:17:15 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_input	file_data;

	if (argc != 2)
		return (print_error("Too many or few arguments provided"), 1);
	ft_bzero(&file_data, sizeof(file_data));
	if (parse_file(argv, &file_data) == 1)
	{
		return (1);
	}
	return (0);
}
