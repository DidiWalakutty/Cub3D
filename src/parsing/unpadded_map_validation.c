/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpadded_map_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:36:05 by yasamankari       #+#    #+#             */
/*   Updated: 2025/04/06 13:49:26 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_first_and_last_rows(char **grid, int height)
{
	char	*trimmed_row;

	trimmed_row = ft_strtrim(grid[0], " ");
	if (!trimmed_row || !check_line_for_walls(trimmed_row))
		return (free(trimmed_row), false);
	free(trimmed_row);
	trimmed_row = ft_strtrim(grid[height - 1], " ");
	if (!trimmed_row || !check_line_for_walls(trimmed_row))
		return (free(trimmed_row), false);
	free(trimmed_row);
	return (true);
}

static bool	check_middle_rows(char **grid, int height)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (i < height - 1)
	{
		len = ft_strlen(grid[i]);
		j = 0;
		while (grid[i][j] == ' ')
			j++;
		if (grid[i][j] != '1')
			return (false);
		while (len > 0 && grid[i][len - 1] == ' ')
			len--;
		if (grid[i][len - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	is_map_surrounded_by_walls_unpadded(char **grid, int height)
{
	if (!check_first_and_last_rows(grid, height))
		return (false);
	if (!check_middle_rows(grid, height))
		return (false);
	return (true);
}
