/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 14:25:31 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/20 14:51:33 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>

# include "MLX42/MLX42.h"
# include "libft.h"

typedef struct s_map
{

}	t_map;

typedef struct s_player
{

}	t_player;

typedef struct s_cub3d
{
	t_map		*map_data;
	t_player	*player;
	mlx_t		*mlx;
	
}	t_cub3d;

#endif