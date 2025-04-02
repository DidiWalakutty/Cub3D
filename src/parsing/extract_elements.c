/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_elements.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 11:14:41 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/04/02 14:51:45 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_texture_prefix(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || \
			ft_strncmp(line, "SO ", 3) == 0 || \
			ft_strncmp(line, "WE ", 3) == 0 || \
			ft_strncmp(line, "EA ", 3) == 0);
}

static bool	handle_floor_color(char *line, t_input *content, \
	bool *f_color)
{
	if (!parse_color(line, content->floor_colors))
		return (false);
	*f_color = true;
	return (true);
}

static bool	handle_ceiling_color(char *line, t_input *content, \
	bool *c_color)
{
	if (!parse_color(line, content->ceiling_colors))
		return (false);
	*c_color = true;
	return (true);
}

static bool	handle_texture(char *line, t_input *content)
{
	printf("Processing texture line: '%s'\n", line);
	return (parse_texture(line, content));
}


// bool	extract_elements(char **lines, t_input *content, \
// 						bool *f_color, bool *c_color)
// {
// 	int		i;
// 	char	*trimmed_line;

// 	i = -1;
// 	while (lines[++i])
// 	{
// 		trimmed_line = ft_strtrim(lines[i], " \t\n\r");
// 		if (!trimmed_line)
// 			return (false);
// 		if (ft_strncmp(trimmed_line, "F ", 2) == 0)
// 		{
// 			if (!handle_floor_color(trimmed_line, content, f_color))
// 				return (free(trimmed_line), false);
// 		}
// 		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
// 		{
// 			if (!handle_ceiling_color(trimmed_line, content, c_color))
// 				return (free(trimmed_line), false);
// 		}
// 		else if (is_texture_prefix(trimmed_line))
// 		{
// 			if (!handle_texture(trimmed_line, content))
// 				return (free(trimmed_line), false);
// 		}
// 		else if (trimmed_line[0] == '\0')
// 		{
// 			free(trimmed_line);
// 			continue ;
// 		}
// 		else if (is_valid_map_char(trimmed_line[0]))
//         {
//             free(trimmed_line);
//             break;
//         }
// 		else
// 			return (free(trimmed_line), false);
// 		free(trimmed_line);
// 	}
// 	return (true);
// }


static bool	process_floor_line(char *line, t_input *content, bool *f_color)
{
    if (!handle_floor_color(line, content, f_color))
    {
        printf("Error: Failed to handle floor color: '%s'\n", line);
        return (false);
    }
    return (true);
}

static bool	process_ceiling_line(char *line, t_input *content, bool *c_color)
{
    if (!handle_ceiling_color(line, content, c_color))
    {
        printf("Error: Failed to handle ceiling color: '%s'\n", line);
        return (false);
    }
    return (true);
}

static bool	process_texture_line(char *line, t_input *content)
{
    if (!handle_texture(line, content))
    {
        printf("Error: Failed to handle texture: '%s'\n", line);
        return (false);
    }
    return (true);
}

static int	process_line(char *line, t_input *content, bool *f_color, bool *c_color)
{
    if (ft_strncmp(line, "F ", 2) == 0)
    {
        printf("Processing floor color line: '%s'\n", line);
        return process_floor_line(line, content, f_color) ? 1 : 0;
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        printf("Processing ceiling color line: '%s'\n", line);
        return process_ceiling_line(line, content, c_color) ? 1 : 0;
    }
    else if (is_texture_prefix(line))
    {
        printf("Processing texture line: '%s'\n", line);
        return process_texture_line(line, content) ? 1 : 0;
    }
    else if (line[0] == '\0')
    {
        printf("Skipping empty line.\n");
        return 1; // Empty line, skip
    }
    else if (is_valid_map_char(line[0]))
    {
        printf("Encountered map data, stopping further processing: '%s'\n", line);
        return STOP_PROCESSING; // Stop processing further lines
    }
    else
    {
        printf("Error: Invalid line: '%s'\n", line);
        return 0; // Error
    }
}

bool	extract_elements(char **lines, t_input *content, bool *f_color, bool *c_color)
{
    int		i;
    char	*trimmed_line;
    int		result;

    i = -1;
    while (lines[++i])
    {
        trimmed_line = ft_strtrim(lines[i], " \t\n\r");
        if (!trimmed_line)
        {
            printf("Error: Failed to trim line %d\n", i);
            return (false);
        }
        printf("Processing line %d: '%s'\n", i, trimmed_line);

        result = process_line(trimmed_line, content, f_color, c_color);
        free(trimmed_line);

        if (result == 0)
        {
            printf("Error: Failed to process line %d\n", i);
            return (false);
        }
        else if (result == STOP_PROCESSING)
        {
            printf("Stopping processing at line %d.\n", i);
            break;
        }
    }
    printf("Successfully processed all lines.\n");
    return (true);
}