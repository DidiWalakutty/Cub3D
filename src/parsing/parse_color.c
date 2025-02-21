/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:35 by ykarimi           #+#    #+#             */
/*   Updated: 2025/02/21 12:34:10 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static bool	free_rgb_values(char **rgb, int count)
{
	while (count > 0)
	{
		count--;
		free(rgb[count]);
	}
	free(rgb);
	return (false);
}
static	bool	split_rgb_values(char *line, char ***rgb)
{
	int	i;

	i = 0;
	*rgb = ft_split(line + 2, ',');
	if (!*rgb)
		return (false);
	while (i < 3)
	{
		if (!(*rgb)[i])
			return (free_rgb_values(*rgb, i));
		i++;
	}
	return (true);
}

static	bool	validate_rgb_values(char **rgb, int *color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!rgb[i])
			return (false);
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
			return (false);
		i++;
	}
	if (rgb[i] != NULL)
		return (false);
	return (true);
}


bool	parse_color(char *line, int *color)
{
	char	**rgb;

	if (!split_rgb_values(line, &rgb))
		return (print_error("Failed parsing colors"), false);
	if (!validate_rgb_values(rgb, color))
	{
		free_rgb_values(rgb, 3);
		return (print_error("Failed parsing colors"), false);
	}
	free_rgb_values(rgb, 3);
	return (true);
}
