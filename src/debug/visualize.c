/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualize.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 12:22:00 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/03/20 21:10:21 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

// // Helper function to draw a line on an image
// void draw_line_on_image(mlx_image_t *img, int x1, int y1, int x2, int y2, uint32_t color)
// {
//     int dx = abs(x2 - x1);
//     int dy = abs(y2 - y1);
//     int sx = x1 < x2? 1: -1;
//     int sy = y1 < y2? 1: -1;
//     int err = (dx > dy? dx: -dy) / 2;

//     while (1)
//     {
//         if (x1 >= 0 && x1 < (int)img->width && y1 >= 0 && y1 < (int)img->height)
//             mlx_put_pixel(img, x1, y1, color);
//         if (x1 == x2 && y1 == y2)
//             break;
//         int e2 = err;
//         if (e2 > -dx)
//         {
//             err -= dy;
//             x1 += sx;
//         }
//         if (e2 < dy)
//         {
//             err += dx;
//             y1 += sy;
//         }
//     }
// }


// // Helper function to draw a rectangle on an image
// void draw_rect_on_image(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
// {
//     for (int i = x; i < x + width; i++)
//     {
//         for (int j = y; j < y + height; j++)
//         {
//             if (i >= 0 && i < (int)img->width && j >= 0 && j < (int)img->height)
//                 mlx_put_pixel(img, i, j, color);
//         }
//     }
// }

// static void visualize_rays_and_walls(t_cub3d *cub3d)
// {
//     t_render *ray = cub3d->render;
//     int TILE_SIZE = 64; // Or whatever your tile size is

//     // Visualize rays
//     for (int x = 0; x < S_WIDTH; x++)
//     {
//         //... (raycasting calculations for column x)...

//         // Calculate ray endpoint
//         int ray_end_x = ray->map_pos.x * TILE_SIZE;
//         int ray_end_y = ray->map_pos.y * TILE_SIZE;

//         // Draw ray (using appropriate MLX42 function)
//         draw_line_on_image(cub3d->scene, ray->player_pos.x * TILE_SIZE, ray->player_pos.y * TILE_SIZE, ray_end_x, ray_end_y, 0xFF0000); // Red color for rays
//     }

//     // Visualize wall heights
//     for (int x = 0; x < S_WIDTH; x++)
//     {
//         //... (wall height calculations for column x)...

//         // Calculate wall slice boundaries
//         int lineheight = (int)S_height / ray->wall_dist;
//         int wall_top = S_height / 2 - lineheight / 2;
//         int wall_bottom = S_height / 2 + lineheight / 2;

//         // Draw wall slice rectangle (using appropriate MLX42 function)
//         draw_rect_on_image(cub3d->scene, x, wall_top, 1, wall_bottom - wall_top, 0x00FF00); // Green color for wall slices
//     }
// }


        // Visualize the wall slice
        // int line_height = (int)(S_height / render->wall_dist);
        // int wall_top = S_height / 2 - line_height / 2;
        // int wall_bottom = S_height / 2 + line_height / 2;

        // // Ensure wall_top and wall_bottom are within screen bounds
        // if (wall_top < 0) wall_top = 0;
        // if (wall_bottom >= S_height) wall_bottom = S_height - 1;

        // Draw rectangle outline for wall slice
        //draw_rect_on_image(cub3d->scene, y, wall_top, 1, wall_bottom - wall_top, 0x00FF00); // Green color for wall slices




		// // Visualize the ray
        // int ray_end_x = render->map_pos.x * 64;
        // int ray_end_y = render->map_pos.y * 64;
        // draw_line_on_image(cub3d->scene, render->player_pos.x * 64 , render->player_pos.y * 64 , ray_end_x, ray_end_y, 0xFF0000); // Red color for rays

void	fps_hook(void *param)
{
	static uint32_t	fps;
	t_cub3d			*meta;

	meta = param;
	if (!(meta->fps_timer.time_func))
	{
		fps = 0;
		timer_init(&meta->fps_timer, mlx_get_time);
	}
	if (timer_delta(&meta->fps_timer) >= 1)
	{
		meta->fps = fps;
		printf("FPS: [%u]\n", meta->fps);
		timer_start(&meta->fps_timer);
		fps = 0;
	}
	else
		fps++;
}

