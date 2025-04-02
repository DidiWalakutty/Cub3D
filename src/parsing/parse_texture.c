/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:16:53 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/04/02 12:36:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	has_png_extension(const char *filename)
{
	const char	*ext;
	size_t		len;
	size_t		ext_len;

	ext = ".png";
	ext_len = ft_strlen(ext);
	len = ft_strlen(filename);
	if (len < ext_len)
		return (print_error("Texture doesn't have png extension."), false);
	return (ft_strncmp(filename + len - ext_len, ext, ext_len) == 0);
}

static bool	set_texture(char *line, char **texture, const char *prefix)
{
	char	*texture_path;
	char	*trimmed;
	printf("Checking line for prefix '%s': '%s'\n", prefix, line);
	if (ft_strncmp(line, prefix, ft_strlen(prefix)) == 0)
	{
		printf("Prefix '%s' matched. Extracting texture path.\n", prefix);
		texture_path = ft_strdup(line + ft_strlen(prefix));
		if (!texture_path)
			return (false);
		trimmed = ft_strtrim(texture_path, " \t\n\r");
		free(texture_path);
		if (!trimmed)
			return (false);
		if (!has_png_extension(trimmed))
		{
			free(trimmed);
			return (false);
		}
		if (*texture)
		{
			free(*texture);
		}
		*texture = trimmed;
		printf("Texture set successfully: '%s'\n", *texture);
		return (true);
	}
	return (false);
}



bool	validate_textures(t_input *content)
{
	printf("Validating textures...\n");
    printf("North texture: '%s'\n", content->north_texture);
    printf("South texture: '%s'\n", content->south_texture);
    printf("West texture: '%s'\n", content->west_texture);
    printf("East texture: '%s'\n", content->east_texture);
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
	printf("Parsing texture line: '%s'\n", line);
	if (set_texture(line, &content->north_texture, "NO ") || \
		set_texture(line, &content->south_texture, "SO ") || \
		set_texture(line, &content->west_texture, "WE ") || \
		set_texture(line, &content->east_texture, "EA "))
		{
			printf("Texture parsed successfully.\n");
			return (true);
		}
	print_error("Failed to parse texture line");
	return (false);
}

