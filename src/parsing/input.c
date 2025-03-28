/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:23 by ykarimi           #+#    #+#             */
/*   Updated: 2025/03/28 11:32:01 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_file_empty(char *file_content)
{
	while (*file_content)
	{
		if (!ft_isspace((unsigned char)*file_content))
			return (false);
		file_content++;
	}
	return (print_error("File is empty."), true);
}

static bool	is_file_extension_valid(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		return (print_error("File extension is not valid."), false);
	return (true);
}

/*
might need to improve the logic of this function, and/or get_next_line
*/
static char	*read_file(const char *pathname)
{
	int		fd;
	char	*line;
	char	*line_joined;
	char	*temp;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (print_error("Could not open file"), NULL);
	line_joined = ft_strdup("");
	if (!line_joined)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp = ft_strjoin(line_joined, line);
		free(line_joined);
		line_joined = temp;
		free(line);
	}
	close(fd);
	return (line_joined);
}

int	handle_input(const char *filename, char ***lines)
{
	char	*file_content;

	if (!is_file_extension_valid(filename))
		return (1);
	file_content = read_file(filename);
	if (!file_content)
		return (1);
	if (is_file_empty(file_content))
		return (free(file_content), 1);
	*lines = ft_split(file_content, '\n');
	free(file_content);
	if (!*lines)
		return (1);
	return (0);
}
