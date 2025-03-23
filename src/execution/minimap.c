/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:23:05 by yasamankari       #+#    #+#             */
/*   Updated: 2025/03/23 10:35:15 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void clear_minimap_image(t_cub3d *game)
{
    t_minimap *minimap;

    minimap = game->minimap;
    if (game->minimap->minimap_img)
        mlx_delete_image(game->mlx, minimap->minimap_img);
    minimap->minimap_img = mlx_new_image(game->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
    if (!minimap->minimap_img)
        end_game(game, "Couldn't render minimap.");
}

static uint32_t get_cell_color(t_cub3d *game, int row, int col)
{
    t_minimap *minimap;
    t_map *map;

    minimap = game->minimap;
    map = game->input->map;

    // Add bounds checking
    if (row < 0 || row >= (int)map->height || col < 0 || col >= (int)ft_strlen(map->grid[row]))
    {
        printf("Out of bounds access: row: %d, col: %d\n", row, col);
        return minimap->floor_color; // Return a default color for out of bounds
    }

    //printf("row: %d, col: %d, meow: %c\n", row, col, map->grid[row][col]);
    if (map->grid[row][col] == '1')
        return minimap->wall_color;
    else if (row == (int)game->render->player_pos.y && col == (int)game->render->player_pos.x)
    {
        //printf("huh\n");
        return minimap->player_color;
    }
    else
    {
        //printf("kkk\n");
        return minimap->floor_color;
    }
}

static void draw_minimap_cell(t_cub3d *game, int x, int y, uint32_t color)
{
    t_minimap *minimap;
    int i;
    int j;

    i = 0;
    minimap = game->minimap;
    while (i < minimap->scale && x + i < minimap->w)
    {
        j = 0;
        while (j < minimap->scale && y + j < minimap->h)
        {
            mlx_put_pixel(minimap->minimap_img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

static void draw_minimap(t_cub3d *game, int row, int col)
{
    t_minimap *minimap;
    //t_map *map;
    uint32_t color;
    int x;
    int y;

    minimap = game->minimap;
    //map = game->input->map;
    x = col * minimap->scale;
    y = row * minimap->scale;
    color = get_cell_color(game, row, col);
    draw_minimap_cell(game, x, y, color);
}

void draw_minimap_grid(t_cub3d *game)
{
    int row;
    int col;
    //t_minimap *minimap;
    t_map *map;

    row = 0;
    //minimap = game->minimap;
    map = game->input->map;
    while (row < (int)map->height)
    {
        col = 0;
        while (col < (int)ft_strlen(map->grid[row])) // Get the width for each line from the map
        {
            draw_minimap(game, row, col);
            col++;
        }
        row++;
    }
}
