/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 14:25:31 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/20 18:44:52 by ykarimi       ########   odam.nl         */
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


typedef struct s_grid
{
	char	**map;
	// int		width;
	// int		height;
	
}		t_grid;

typedef struct s_parsing
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_colors[3];
	int		ceiling_colors[3];
	t_grid	*grid;

}	t_file_content;

// typedef struct s_player
// {

// }	t_player;

// typedef struct s_cub3d
// {
// 	t_map		*map_data;
// 	t_player	*player;
// 	mlx_t		*mlx;
	
// }	t_cub3d;


/* Input validation Functions */
int		parse_file(int argc, char *argv[]);
char	*read_file(char *pathname);
int		validate_map_extension(const char *filename);
/* Error Handling Functions */
void	print_error(char *errormsg);


#endif