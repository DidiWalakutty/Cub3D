/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 14:25:31 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 11:50:24 by ykarimi       ########   odam.nl         */
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

typedef struct s_player
{
	int		x;
	int		y;
	char	orientation;
	int		player_count;

}	t_player;


typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			first_index;
	int			last_index;
	t_player	*player;
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


typedef struct s_cub3d
{
	t_input		*input;
	t_map		*map_data;
	t_player	*player;
	mlx_t		*mlx;
}	t_cub3d;


/* File Parsing */
int		handle_input(const char *filename, char ***lines);
int		parse_file(char *argv[], t_input *file_data);
bool	extract_elements(char **lines, t_input *content);
//bool	parse_map(char **lines, t_input *content);
bool	parse_texture(char *line, t_input *content);
bool	parse_color(char *line, int *color);
bool is_map_last_in_file(char **lines, t_map *map);
//bool	is_map_last_in_file(char **lines, int map_start_index);
bool	handle_map(t_input *file_data, char **lines);


/* Map Validation */
bool	is_valid_map_char(char c);
bool	validate_map_characters(t_map *map);
bool	is_map_surrounded_by_walls(t_map *map);
bool 	validate_textures(t_input *content);

/* Map Population */
void	get_map_dimensions(t_map *map);
int		populate_map(t_input *file_data);
void	set_player_spawning_point(t_map *map, t_player *player);
int		check_player_spawning_point(t_player *player);

/* Error Handling */
void	print_error(char *errormsg);
void	cleanup(t_cub3d *game);

/* Print for testing */
void	print_parsed_content(t_input *content);
void	print_map(char **map);

#endif
