/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:53 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/02/12 19:05:57 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	bool has_png_extension(const char *filename)
{
	const char	*ext;
	size_t		len;
	size_t		ext_len;

	ext = ".xpm";
	ext_len = ft_strlen(ext);
	len = ft_strlen(filename);
	if (len < ext_len)
		return (print_error("Texture doesn't have png extension."), false);
	return (ft_strncmp(filename + len - ext_len, ext, ext_len) == 0);
}
// static bool texture_exists(const char *filename)
// {
//     struct stat buffer;
//     return (stat(filename, &buffer) == 0);
// }


// static	bool is_texture_duplicate(const char *texture, t_input *content)
// {
// 	size_t	len;

// 	len = ft_strlen(texture);
// 	return (content->north_texture && ft_strncmp(texture, content->north_texture, len) == 0) ||
// 		(content->south_texture && ft_strncmp(texture, content->south_texture, len) == 0) ||
// 		(content->west_texture && ft_strncmp(texture, content->west_texture, len) == 0) ||
// 		(content->east_texture && ft_strncmp(texture, content->east_texture, len) == 0);
// }

static	bool set_texture(char *line, char **texture, const char *prefix, t_input *content)
{
	char	*texture_path;
	char	*trimmed;

	if (ft_strncmp(line, prefix, ft_strlen(prefix)) == 0)
	{
		texture_path = ft_strdup(line + ft_strlen(prefix));
		trimmed = ft_strtrim(texture_path, " \t\n\r");
		free(texture_path);
		if (!has_png_extension(trimmed))
			return (free(trimmed), false);
		// if (is_texture_duplicate(texture_path, content))
		// {
		// 	printf("Duplicate texture: %s\n", texture_path);
		// 	free(texture_path);
		// 	return false;
		// }
		// if (!texture_exists(texture_path))
		// {
		//     printf("Texture file does not exist: %s\n", texture_path);
		//     free(texture_path);
		//     return false;
		// }
		*texture = trimmed;
		free(trimmed);
		return (true);
	}
	return (false);
}

bool	validate_textures(t_input *content)
{
	if (!content->north_texture)
	{
		print_error("Missing North Texture.");
		return (false);
	}
	if (!content->south_texture)
	{
		print_error("Missing South Texture.");
		return (false);
	}
	if (!content->west_texture)
	{
		print_error("Missing West Texture.");
		return (false);
	}
	if (!content->east_texture)
	{
		print_error("Missing East Texture.");
		return (false);
	}
	return (true);
}


bool	parse_texture(char *line, t_input *content)
{
	if (set_texture(line, &content->north_texture, "NO ", content) ||
		set_texture(line, &content->south_texture, "SO ", content) ||
		set_texture(line, &content->west_texture, "WE ", content) ||
		set_texture(line, &content->east_texture, "EA ", content))
			return (true);
	print_error("Failed to parse texture line");
	return (false);
}
