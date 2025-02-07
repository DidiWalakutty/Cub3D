/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 14:25:31 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/07 21:33:57 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <stdint.h>
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

// Define ray info
# define FOV 60				// field of view
# define PI 3.1415926		// PI
# define SPEED 0.1			// move speed
# define ROTATE_S 0.02			// rotate speed
# define WALL_MARGIN 0.05	// collision buffer for diaganol movement
# define X_SIDE 0
# define Y_SIDE 1

// Define movement
# define FORWARD 1
# define BACKWARDS -1
# define RIGHT 1
# define LEFT -1
# define TURN_RIGHT 1
# define TURN_LEFT -1


typedef struct s_dvectr
{
	double	x;
	double	y;
}	t_dvectr;

typedef struct s_ivect
{
	int32_t	x;
	int32_t	y;
}	t_ivectr;

typedef struct s_draw
{
	int32_t	height;
	int32_t	start;
	int32_t	end;
}	t_draw;

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
	mlx_texture_t	*wall_img;
	int32_t			floor_color;
	int32_t			ceiling_color;
	double			wall_x_pos;
	double			pix_step;
	double			tex_pos;
	int				x_tex;
	int				y_tex;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}	t_textures;

// Renders the game world, incl walls, floors, ceiling onto the screen.
// Info like players pos, direction, raycasting results. The engine
// determines the appropriate colors to render the walls.
typedef struct s_render
{
	mlx_image_t	*scene;
	mlx_image_t	*floor_and_ceiling;
	t_dvectr	plane;
	t_dvectr	player_pos;
	t_dvectr	player_dir;
	t_dvectr	ray_dir;
	t_dvectr	delta_dist;
	t_dvectr	side_dist;
	double		camera_column;
	t_ivectr	map_pos;	// pos in the map
	t_ivectr	step;		// dir of step
	t_draw		line;
	int			wall_hit;	// x or y-side
	double		wall_dist;	// player_dist from wall
	float		fov;
}	t_render;

typedef struct s_cub3d
{
	t_input		*input;
	// t_map		*map_data;
	t_player	*player;
	t_render	*render;
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
void	keys(void *param);
bool	path_clear(char **grid, t_dvectr player_pos, t_dvectr new, t_dvectr dir);
bool	hit_wall(char **grid, int32_t x, int32_t y);
void	create_ray(t_cub3d *cub3d, t_render *ray, size_t screen_i);
void	loop_screenpixels(t_render *ray, t_textures	*text, mlx_texture_t *wall);

/*Set Up*/
void	init_settings(t_cub3d *cub3d, t_player *player);
bool	alloc_execution_structs(t_cub3d *cub3d);
t_render	*set_variables(t_cub3d *cub3d, t_player *player);

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
