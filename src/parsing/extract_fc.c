/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_fc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/03 16:21:15 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/04/03 16:34:45 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	handle_floor_color(char *line, t_input *content, \
	bool *f_color)
{
	if (!parse_color(line, content->floor_colors))
		return (false);
	*f_color = true;
	return (true);
}

bool	handle_ceiling_color(char *line, t_input *content, \
	bool *c_color)
{
	if (!parse_color(line, content->ceiling_colors))
		return (false);
	*c_color = true;
	return (true);
}

bool	process_floor_line(char *line, t_input *content, bool *f_color)
{
	if (!handle_floor_color(line, content, f_color))
		return (false);
	return (true);
}

bool	process_ceiling_line(char *line, t_input *content, bool *c_color)
{
	if (!handle_ceiling_color(line, content, c_color))
		return (false);
	return (true);
}
