/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_text.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/03 16:22:36 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/04/03 16:34:58 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	handle_texture(char *line, t_input *content)
{
	return (parse_texture(line, content));
}

bool	is_texture_prefix(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || \
			ft_strncmp(line, "SO ", 3) == 0 || \
			ft_strncmp(line, "WE ", 3) == 0 || \
			ft_strncmp(line, "EA ", 3) == 0);
}
