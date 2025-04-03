/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/03 15:58:01 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/04/03 16:30:40 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**allocate_lines_array(size_t line_count)
{
	char	**lines;

	lines = ft_calloc(line_count + 1, sizeof(char *));
	if (!lines)
		print_error("Memory allocation failed");
	return (lines);
}

static char	*extract_line(const char **start, const char *newline)
{
	char	*line;

	if (newline)
	{
		line = ft_substr(*start, 0, newline - *start);
		*start = newline + 1;
	}
	else
	{
		line = ft_strdup(*start);
		*start += ft_strlen(*start);
	}
	return (line);
}

static void	free_lines(char **lines, size_t count)
{
	while (count > 0)
		free(lines[--count]);
	free(lines);
}

static bool	process_line_split(const char **start, const char *newline, \
										char **lines, size_t index)
{
	lines[index] = extract_line(start, newline);
	if (!lines[index])
		return (false);
	return (true);
}

char	**split_file_content(const char *file_content)
{
	char		**lines;
	size_t		line_count;
	size_t		i;
	const char	*start;
	const char	*newline;

	if (!file_content)
		return (NULL);
	line_count = count_lines(file_content);
	lines = allocate_lines_array(line_count);
	if (!lines)
		return (NULL);
	i = 0;
	start = file_content;
	while (*start)
	{
		newline = ft_strchr(start, '\n');
		if (!process_line_split(&start, newline, lines, i++))
		{
			free_lines(lines, i - 1);
			return (NULL);
		}
	}
	lines[i] = NULL;
	return (lines);
}
