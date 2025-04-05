/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_padding.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/05 13:05:32 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/04/05 13:23:36 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_line_length(char **grid)
{
	int	max_length;
	int	i;
	int	line_length;

	max_length = 0;
	i = 0;
	while (grid[i])
	{
		line_length = ft_strlen(grid[i]);
		if (line_length > max_length)
			max_length = line_length;
		i++;
	}
	return (max_length);
}

static void	replace_spaces_in_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == ' ')
			line[j] = '1';
		j++;
	}
}

static char	*pad_line_with_ones(char *line, int max_length)
{
	int		j;
	char	*padded_line;

	padded_line = malloc(max_length + 1);
	if (!padded_line)
	{
		print_error("Memory allocation failed while padding lines.");
		return (NULL);
	}
	ft_strlcpy(padded_line, line, max_length + 1);
	j = ft_strlen(line);
	while (j < max_length)
		padded_line[j++] = '1';
	padded_line[j] = '\0';
	return (padded_line);
}

/* Main function to replace spaces with '1' and pad lines */
void	replace_spaces_with_one(char **grid)
{
	int		i;
	int		max_length;
	char	*padded_line;

	max_length = get_max_line_length(grid);
	i = 0;
	while (grid[i])
	{
		replace_spaces_in_line(grid[i]);
		if ((int)ft_strlen(grid[i]) < max_length)
		{
			padded_line = pad_line_with_ones(grid[i], max_length);
			if (!padded_line)
				return ;
			free(grid[i]);
			grid[i] = padded_line;
		}
		i++;
	}
}
