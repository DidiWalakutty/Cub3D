/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 14:25:31 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/29 20:51:50 by diwalaku      ########   odam.nl         */
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

// Define sizes
# define S_WIDTH 1800		// screen width
# define S_HEIGTH 1200		// screen heigth
# define S_UPPER_HALF 900	// upper half of screen
# define S_LOWER_HALF 600	// lower half of screen
# define FOV 60				// field of view
# define PI 3.1415926		// PI

typedef struct s_vectr
{
	double	x;
	double	y;
}	t_vectr;

typedef struct s_player
{
	int		x;
	int		y;
	char	orientation;
	int		player_count;
	float	fov;
	float	rotation;
	t_vectr	position;
	t_vectr	direction;
	t_vectr	plane;
}	t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			first_index;
	int			last_index;
	t_player	*player;
}	t_map;

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

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	int32_t			floor_color;
	int32_t			ceiling_color;
}	t_textures;

// Renders the game world, incl walls, floors, ceiling onto the screen.
// Info like players pos, direction, raycasting results. The engine
// determines the appropriate colors to render the walls.
typedef struct s_render
{
	mlx_image_t	*wall;
	mlx_image_t	*floor_and_ceiling;
}	t_render;

typedef struct s_cub3d
{
	t_input		*input;
	t_map		*map_data;
	t_player	*player;
	t_render	render;
	mlx_t		*mlx;
	t_textures	*textures;
}	t_cub3d;


/* File Parsing */
int		handle_input(const char *filename, char ***lines);
int		parse_file(char *argv[], t_input *file_data);
bool	extract_elements(char **lines, t_input *content);
bool	parse_texture(char *line, t_input *content);
bool	parse_color(char *line, int *color);
bool 	is_map_last_in_file(char **lines, t_map *map);
bool	handle_map(t_input *file_data, char **lines);

/* Map Validation */
bool	is_valid_map_char(char c);
bool	validate_map_characters(t_map *map);
bool	is_map_surrounded_by_walls(t_map *map);
bool 	validate_textures(t_input *content);

/* Map Population */
void	set_player_spawning_point(t_map *map, t_player *player);
int		check_player_spawning_point(t_player *player);

/*Execution*/
void	run_cub3d(t_cub3d *cub3d);

/*Set Up*/
void	init_settings(t_cub3d *cub3d);
int32_t	get_rgba(int colors[3], int32_t a);
bool	alloc_execution_structs(t_cub3d *cub3d);

/*Images and Textures*/
bool	load_wall_textures(t_cub3d *cub3d);
void	fill_background(t_cub3d *cub3d);

/* Error Handling */
void	print_error(char *errormsg);
void	cleanup(t_cub3d *game);
void	end_game(t_cub3d *cub3d, char *error_message);

/* Print for testing */
void	print_parsed_content(t_input *content);
void	print_map(char **map);

#endif
