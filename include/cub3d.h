/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:25:31 by diwalaku          #+#    #+#             */
/*   Updated: 2025/01/22 18:43:32 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "MLX42.h"
# include "libft.h"


typedef struct s_map
{
	char	**grid;
	// int		width;
	// int		height;
	
}		t_map;

typedef struct s_input
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_colors[3];
	int		ceiling_colors[3];
	t_map	*map;

}	t_input;

// typedef struct s_player
// {

// }	t_player;

// typedef struct s_cub3d
// {
// 	t_map		*map_data;
// 	t_player	*player;
// 	mlx_t		*mlx;
	
// }	t_cub3d;


/* Input Handling */
char	*read_file(const char *pathname);
int		validate_map_extension(const char *filename);

/* File Parsing */
int		parse_file(char *argv[], t_input *file_data);
bool	extract_elements_from_file(char **lines, t_input *content, int *map_start_index);
bool	is_file_empty(char *file_content);
bool	parse_map(char **lines, t_input *content, int map_start_index);
bool	parse_texture(char *line, t_input *content);
bool	parse_color(char *line, int *color);
bool	is_map_last_in_file(char **lines, int map_start_index);
int		handle_input(const char *filename, char ***lines);

/* Map Validation */
bool	is_valid_map_char(char c);
bool	is_map_surrounded_by_walls(char **map);
bool 	validate_textures(t_input *content);

/* Error Handling Functions */
void	print_error(char *errormsg);
void	print_parsed_content(t_input *content);

#endif
