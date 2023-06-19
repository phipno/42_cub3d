/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:48:45 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/19 16:36:25 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "MLX42.h"
#include "libft.h"
#include "raycasting.h"

#include <math.h>

void DDA(int X0, int Y0, int X1, int Y1, t_all cub, int32_t color)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
		if ((X >= 0 && X < WIDTH) && (Y >= 0 && Y < HEIGHT))
        	mlx_put_pixel(cub.image_player, X, Y, color); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}


void	draw_heaven_and_hell(t_all cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(cub.image_background, x, y, cub.map.sky_color.colour);
			else
				mlx_put_pixel(cub.image_background, x, y, cub.map.floor_color.colour);
			x++;
		}
		y++;
	}
}

// //grid
// void	draw_square(int y, int x, t_all cub, int32_t color)
// {
// 	for (int i = y * 64; i < y * 64 + 64; i++)
// 	{
// 		for (int j = x * 64; j < x * 64 + 64; j++)
// 		{
// 			if (j == x * 64 || i % 64 == 0)
// 				mlx_put_pixel(cub.image_game, j, i, 0xFFFFFFFF);
// 			else
// 				mlx_put_pixel(cub.image_game, j, i, color);
// 		}
// 	}
// }


// void	draw_map(t_all cub)
// {
// 	for (size_t y = 0; y < cub.map.map_line_max; y++)
// 	{
// 		for (size_t x = 0; x < cub.map.map_column_max; x++)
// 		{
// 			if (cub.map.a_map[y][x] == '1')
// 				draw_square(y, x, cub, 0x000000FF);
// 			else
// 				draw_square(y, x, cub, 0xAAAAAAFF);
// 		}
// 	}
// }

double	pythagoras(float ax, float ay, float bx, float by)
{
	return (sqrt(( bx - ax ) * ( bx - ax ) + (by - ay) * (by - ay)));
}

t_raycaster	draw_rays_verti(t_all cub)
{
	t_raycaster ray;
	int		map_x, map_y, depth_of_field;

	ray.dir = cub.per.direction;
	depth_of_field = 0;
	float nTan = -tan(ray.dir);
	if (ray.dir > P2 && ray.dir < P3)
	{
		ray.x = (((int)cub.per.st.x >> 6) << 6) - 0.0001;
		ray.y = (cub.per.st.x - ray.x) * nTan + cub.per.st.y;
		ray.x_offset = -64;
		ray.y_offset = -ray.x_offset * nTan;
		ray.color = 0xAAAAAAFF;
		ray.cardinal_dir = EAST;
	}
	if (ray.dir < P2 || ray.dir > P3)
	{
		ray.x = (((int)cub.per.st.x >> 6) << 6) + 64;
		ray.y = (cub.per.st.x - ray.x) * nTan + cub.per.st.y;
		ray.x_offset = 64;
		ray.y_offset = -ray.x_offset * nTan;
		ray.color = 0x0000AAFF;
		ray.cardinal_dir = WEST;
	}
	if (ray.dir == P2 || ray.dir == P3)
	{
		ray.x = cub.per.st.x;
		ray.y = cub.per.st.y;
		depth_of_field = 16;
		ray.color = 0x444444FF;
		//@note fixing on which side its on
		ray.cardinal_dir = SOUTH;
	}
	// printf("HORI_Ray   Off_X%f Off_Y%f\n", ray.x_offset, ray.y_offset);
	while (depth_of_field < 16)
	{
		map_x = (int)(ray.x) >> 6;
		map_y = (int)(ray.y) >> 6;
		if (map_y >= 0 && map_y < (int)cub.map.map_line_max && map_x >= 0 && map_x < (int)cub.map.map_column_max &&
			cub.map.a_map[map_y][map_x] == '1')
			depth_of_field = 16;
		else
		{
			ray.x += ray.x_offset;
			ray.y += ray.y_offset;
			depth_of_field++;
		}
	}
	// printf("MAPX %d   MAPY %d\n", map_x, map_y);
	ray.distance_raw = pythagoras(cub.per.st.x, cub.per.st.y, ray.x, ray.y);
	return (ray);
}

t_raycaster	draw_rays_hori(t_all cub)
{
	t_raycaster ray;
	int		map_x, map_y, depth_of_field;


	ray.dir = cub.per.direction;
	depth_of_field = 0;
	float aTan = -1/tan(ray.dir);
	if (ray.dir > PI)
	{
		//looking up
		ray.y = (((int)cub.per.st.y >> 6) << 6) - 0.0001;
		ray.x = (cub.per.st.y - ray.y) * aTan + cub.per.st.x;
		ray.y_offset = (int)-64;
		ray.x_offset = -ray.y_offset * aTan;
		ray.color = 0xAA0000FF;
		ray.cardinal_dir = SOUTH;
	}
	if (ray.dir < PI)
	{
		//looking down
		ray.y =  (((int)cub.per.st.y >> 6) << 6) + 64;
		ray.x = (cub.per.st.y - ray.y) * aTan + cub.per.st.x;
		ray.y_offset = 64;
		ray.x_offset = -ray.y_offset * aTan;
		ray.color = 0x00AA00FF;
		ray.cardinal_dir = NORTH;
	}
	if (ray.dir == 0 || ray.dir == PI)
	{
		//looking straigt left or right
		ray.x = cub.per.st.x;
		ray.y = cub.per.st.y;
		depth_of_field = 16;
		ray.color = 0x444444FF;
		//@note fixing on which side its on
		ray.cardinal_dir = NORTH;
	}
	// printf("HORI_Ray   Off_X%f Off_Y%f\n", ray.x_offset, ray.y_offset);
	while (depth_of_field < 16)
	{
		// divided or multi
		map_x = (int)(ray.x) >> 6;
		map_y = (int)(ray.y) >> 6;
		if (map_y >= 0 && map_y < (int)cub.map.map_line_max && map_x >= 0 && map_x < (int)cub.map.map_column_max &&
			cub.map.a_map[map_y][map_x] == '1')
			depth_of_field = 16;
		else
		{
			ray.x += ray.x_offset;
			ray.y += ray.y_offset;
			depth_of_field++;
		}
	}
	// printf("MAPX %d   MAPY %d\n", map_x, map_y);
	ray.distance_raw = pythagoras(cub.per.st.x, cub.per.st.y, ray.x, ray.y);
	// printf("PX%f  PY%f   RX%f  RY%f\n", cub.per.st.x, cub.per.st.y, ray.x, ray.y);
	return (ray);
}

void	draw_walls(t_all cub, int x, t_raycaster wall_ray)
{
	int		line_h;
	int		line_offset;
	double	angle;

	// int		offset;

	// angle fixes the distortion from walls on the same
	// grid line not being displayed on the same y height
	// in short fixes fish eye
	angle = (cub.per.angle_real / 180 * PI) - cub.per.direction;
	if (angle < 0)
		angle = angle + 2 * PI;
	if (angle > 2 * PI)
		angle = angle - 2 * PI;
	wall_ray.distance_parralel = cos(angle) * wall_ray.distance_raw;


	//for the offset we need to know at what pixel of a wall were
	//looking and where is the wall end. to calculate a factor so we can
	//increment it in rotational way.

	line_h = 64 * HEIGHT / wall_ray.distance_parralel;
	if (line_h > HEIGHT)
		line_h = HEIGHT;
	line_offset = HEIGHT/2 - line_h / 2;
	while (line_h >= 0)
	{
		if ((x >= 0 && x < WIDTH) && (line_h + line_offset >= 0 && line_h + line_offset < HEIGHT))
			mlx_put_pixel(cub.image_game, x, line_h + line_offset, get_rgba(
			cub.map.mlx_wall[wall_ray.cardinal_dir]->pixels[0 * offset],
			cub.map.mlx_wall[wall_ray.cardinal_dir]->pixels[1 * offset],
			cub.map.mlx_wall[wall_ray.cardinal_dir]->pixels[2 * offset],
			cub.map.mlx_wall[wall_ray.cardinal_dir]->pixels[3 * offset]));
		line_h--;
	}
}

void	draw_player(t_all cub)
{
	// (void)cub;

	//printf("element.size_x [%f] element.size_y [%f]\n", cub.minimap.element.size_x, cub.minimap.element.size_y);
	// printf("Pos%f Pos%f\n", cub.per.pos.x, cub.per.pos.y);
	cub.per.st.x = cub.per.pos.x;
	cub.per.st.y = cub.per.pos.y;
	// draw_map(cub);
	// for (int y = cub.per.pos.y * 64; y < cub.per.pos.y * 64 + 10; y++)
	// {
	// 	for (int x = cub.per.pos.x * 64; x < cub.per.pos.x * 64 + 10; x++)
	// 	{
	// 		mlx_put_pixel(cub.image_game, x, y, 0xFFFF55FF);
	// 	}
	// }
	double	angle_add;
	t_raycaster rays[2];
	// printf("direction [%f] | angle_add [%f]\n", cub.per.direction, angle_add);
	cub.per.direction = (cub.per.angle_real / 180 * PI) - cub.per.fov / 2;
	angle_add = (cub.per.fov / WIDTH);
	//printf("direction [%f] | angle_add [%f]\n", cub.per.direction, angle_add);
	for (int x = 0; x < WIDTH; x++)
	{
		if (cub.per.direction < 0)
			cub.per.direction = cub.per.direction + 2 * PI;
		if (cub.per.direction > 2 * PI)
			cub.per.direction = cub.per.direction - 2 * PI;
		// printf("Angle.%d %f\n", x, cub.per.direction);
		rays[0] = draw_rays_hori(cub);
		rays[1] = draw_rays_verti(cub);
		if (rays[0].distance_raw < rays[1].distance_raw)
		{
			// printf("Angle [%f]  stX [%f]  stY[%f]  rX[%f]  rY[%f]\n", cub.per.direction, cub.per.st.x, cub.per.st.y, rays[0].x, rays[0].y);
			DDA(cub.per.st.x, cub.per.st.y, rays[0].x, rays[0].y, cub, 0xFF0000FF);
			draw_walls(cub, x, rays[0]);
		}
		else
		{
			// printf("Angle [%f]  stX [%f] | stY [%f] | rX[%f] | rY[%f]\n", cub.per.direction, cub.per.st.x, cub.per.st.y, rays[1].x, rays[1].y);
			DDA(cub.per.st.x, cub.per.st.y, rays[1].x, rays[1].y, cub, 0xFF0000FF);
			draw_walls(cub, x, rays[1]);
		}
		DDA(cub.per.st.x, cub.per.st.y, cub.per.st.x + 30 * cos(cub.per.angle_real / 180 * PI), cub.per.st.y + 30 * sin(cub.per.angle_real / 180 * PI), cub, 0x00FF00FF);
		cub.per.direction += angle_add;
	}

	// mlx_texture_t	*wall;
	// mlx_image_t		*i;

	// wall = mlx_load_png(cub.map.north_wall);
	// i = mlx_texture_to_image(cub.mlx, wall);
	// mlx_image_to_window(cub.mlx, i, 300, 300);

}

/* ************************************************************************** */
