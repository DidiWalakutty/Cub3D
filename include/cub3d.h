/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:25:31 by diwalaku          #+#    #+#             */
/*   Updated: 2025/04/06 13:52:28 by yasamankari      ###   ########.fr       */
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

# define STOP_PROCESSING -1

# define S_WIDTH 1200
# define S_HEIGHT 1000

/* Define ray info */
# define SPEED 0.08
# define X_SIDE 0
# define Y_SIDE 1

/* Define movement */
# define FORWARD 1
# define BACKWARDS -1
# define RIGHT -1
# define LEFT 1

/* Minimap dimension */
# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200

/* Minimap colors */
# define PLAYER_COLOR 0xFF0000FF
# define WALL_COLOR 0x00008BFF
# define FLOOR_COLOR 0xF8F8FFFF

typedef struct s_cub3d	t_cub3d;

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
	size_t		width;
	size_t		height;
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
	bool	has_floor_color;
	bool	has_ceiling_color;
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
	double			pix_step;
	double			tex_pos;
	int				x_tex;
	int				y_tex;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}	t_textures;

typedef struct s_render
{
	t_dvectr	plane;
	t_dvectr	player_pos;
	t_dvectr	player_dir;
	t_dvectr	ray_dir;
	t_dvectr	delta_dist;
	t_dvectr	side_dist;
	double		camera_column;
	t_ivectr	map_pos;
	t_ivectr	map_step;
	int			side_hit;
	double		wall_height;	
	double		wall_dist;
}	t_render;

typedef struct s_minimap
{
	int			w;
	int			h;
	double		scale;
	uint32_t	player_color;
	uint32_t	wall_color;
	uint32_t	floor_color;
	t_ivectr	player_pos;
	mlx_image_t	*minimap_img;
}	t_minimap;

typedef struct s_cub3d
{
	mlx_image_t	*scene;
	mlx_image_t	*floor_and_ceiling;
	t_input		*input;
	t_render	*render;
	mlx_t		*mlx;
	t_textures	*textures;
	t_minimap	*minimap;
}	t_cub3d;

/* File Parsing */
int			handle_input(const char *filename, char ***lines);
int			parse_file(char *argv[], t_input *file_data);
bool		extract_elements(char **lines, t_input *content, \
							bool *has_floor_color, bool *has_ceiling_color);
bool		parse_texture(char *line, t_input *content);
bool		parse_color(char *line, int *color);
bool		is_map_last_in_file(char **lines, t_map *map);
bool		handle_map(t_input *file_data, char **lines);
bool		is_player_entrapped(t_map *map);
bool		update_map_dimensions(const char *line, t_map *map, int i);
char		**split_file_content(const char *file_content);
size_t		count_lines(const char *file_content);
bool		is_texture_prefix(const char *line);
bool		handle_texture(char *line, t_input *content);
bool		process_ceiling_line(char *line, t_input *content, bool *c_color);

bool		process_floor_line(char *line, t_input *content, bool *f_color);
bool		process_ceiling_line(char *line, t_input *content, bool *c_color);
bool		handle_floor_color(char *line, t_input *content, \
							bool *f_color);
bool		handle_ceiling_color(char *line, t_input *content, \
			bool *c_color);
bool		process_floor_line(char *line, t_input *content, bool *f_color);
int			process_line(char *line, t_input *content, \
							bool *f_color, bool *c_color);
int			process_map_or_empty_line(char *line);
int			process_element_line(char *line, t_input *content, \
									bool *f_color, bool *c_color);
bool		process_texture_line(char *line, t_input *content);
void		replace_spaces_with_one(char **grid);
bool		process_map_lines(char **lines, t_map *map);
bool		process_single_map_line(const char *line, t_map *map, int i);
bool		check_line_for_walls(const char *line);
bool		is_map_surrounded_by_walls_unpadded(char **grid, int height);
bool		check_first_and_last_rows(char **grid, int height);

/* Map Validation */
bool		is_valid_map_char(char c);
bool		validate_map_characters(t_map *map);
bool		is_map_surrounded_by_walls(t_map *map);
bool		validate_textures(t_input *content);

/* Map Population */
void		set_player_spawning_point(t_map *map, t_player *player);
int			check_player_spawning_point(t_player *player);
bool		get_map_properties(char **lines, t_map *map);
bool		populate_grid(char **lines, t_map *map);
bool		is_texture_or_color_line(const char *line);

/* Execution */
void		run_cub3d(t_cub3d *cub3d);
void		keys(void *param);
bool		path_clear(char **grid, t_map *map, t_dvectr new);
bool		hit_wall(char **grid, t_map *map, int32_t y, int32_t x);
void		update_side_dist(t_render *ray);
void		set_wall_height(t_render *ray);
void		set_wall_textures(t_render *ray, t_cub3d *cub3d);
void		draw_wall_slices(t_cub3d *cub3d, t_textures *text, int x);
void		raycaster(void *data);

/* Set Up */
void		init_settings(t_cub3d *cub3d);
bool		alloc_execution_structs(t_cub3d *cub3d);
t_render	*set_variables(t_cub3d *cub3d);
uint32_t	color_texture(t_textures *text, double x_info, double y_info);

/* Images and Textures */
bool		load_wall_textures(t_cub3d *cub3d);
void		fill_background(t_cub3d *cub3d);

/* Error Handling */
void		print_error(char *errormsg);
void		cleanup(t_cub3d *game);
void		end_game(t_cub3d *cub3d, char *error_message, bool failure);

/* Print for testing */
void		print_parsed_content(t_input *content);
void		print_map(char **map);
void		print_lines(char **lines);

/* Minimap */
void		render_minimap(t_cub3d *game);
void		initialize_minimap(t_minimap *minimap, t_cub3d *game);
void		clear_minimap_image(t_cub3d *game);
void		draw_minimap_grid(t_cub3d *game);

#endif
