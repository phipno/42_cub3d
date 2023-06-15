/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:48:45 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/15 15:43:57 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "MLX42.h"
#include "libft.h"
#include "raycasting.h"

#include <math.h>

//void	draw_direction(t_all *all)
//{
//	double	length;
//	double	width;
//	double	offset;
//	double	x;
//	double	y;
//
//	length = 10;
//	width = 2;
//	offset = all->minimap.element.size_x;
//	x = all->per.pos.x;
//	y = all->per.pox.y;
//	while (y < HEIGHT)
//	{
//		while (x < WIDTH)
//		{
//			x += 1;
//		}
//		x = all->per.pox.x;
//		y += 1;
//	}
//}


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

// void	draw_troll(t_all cub)
// {
// 	int x;
// 	int y;

// 	y = 80;
// 	while (y < HEIGHT - 80)
// 	{
// 		x = 160;
// 		while (x < WIDTH - 160)
// 		{
// 			mlx_put_pixel(cub.image_game, x, y, 0x0);
// 			x++;
// 		}
// 		y++;
// 	}
// 	y = 140;
// 	while (y < HEIGHT -140)
// 	{
// 		x = 0;
// 		while (x < WIDTH - 160 - 160)
// 		{
// 			mlx_put_pixel(cub.image_game, x, y, 0x0);
// 			x++;
// 		}
// 		y++;
// 	}
// 	y = 140;
// 	while (y < HEIGHT -140)
// 	{
// 		x = 320;
// 		while (x < WIDTH)
// 		{
// 			mlx_put_pixel(cub.image_game, x, y, 0x0);
// 			x++;
// 		}
// 		y++;
// 	}
// }

//grid
void	draw_square(int y, int x, t_all cub, int32_t color)
{
	for (int i = y * 64; i < y * 64 + 64; i++)
	{
		for (int j = x * 64; j < x * 64 + 64; j++)
		{
			if (j == x * 64 || i % 64 == 0)
				mlx_put_pixel(cub.image_game, j, i, 0xFFFFFFFF);
			else
				mlx_put_pixel(cub.image_game, j, i, color);
		}
	}
}


void	draw_map(t_all cub)
{
	for (size_t y = 0; y < cub.map.map_line_max; y++)
	{
		for (size_t x = 0; x < cub.map.map_column_max; x++)
		{
			if (cub.map.a_map[y][x] == '1')
				draw_square(y, x, cub, 0x000000FF);
			else
				draw_square(y, x, cub, 0xAAAAAAFF);
		}
	}
}

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
	}
	if (ray.dir < P2 || ray.dir > P3)
	{
		ray.x = (((int)cub.per.st.x >> 6) << 6) + 64;
		ray.y = (cub.per.st.x - ray.x) * nTan + cub.per.st.y;
		ray.x_offset = 64;
		ray.y_offset = -ray.x_offset * nTan;
	}
	if (ray.dir == P2 || ray.dir == P3)
	{
		printf("hi\n");
		ray.x = cub.per.st.x;
		ray.y = cub.per.st.y;
		depth_of_field = 8;
	}
	// printf("HORI_Ray   Off_X%f Off_Y%f\n", ray.x_offset, ray.y_offset);
	while (depth_of_field < 8)
	{
		map_x = (int)(ray.x) >> 6;
		map_y = (int)(ray.y) >> 6;
		if (map_y >= 0 && map_y < (int)cub.map.map_line_max && map_x >= 0 && map_x < (int)cub.map.map_column_max &&
			cub.map.a_map[map_y][map_x] == '1')
			depth_of_field = 8;
		else
		{
			ray.x += ray.x_offset;
			ray.y += ray.y_offset;
			depth_of_field++;
		}
	}
	// printf("MAPX %d   MAPY %d\n", map_x, map_y);
	ray.distance_per = pythagoras(cub.per.st.x, cub.per.st.y, ray.x, ray.y);
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
	}
	if (ray.dir < PI)
	{
		//looking down
		ray.y =  (((int)cub.per.st.y >> 6) << 6) + 64;
		ray.x = (cub.per.st.y - ray.y) * aTan + cub.per.st.x;
		ray.y_offset = 64;
		ray.x_offset = -ray.y_offset * aTan;
	}
	if (ray.dir == 0 || ray.dir == PI)
	{
		//looking straigt left or right
		ray.x = cub.per.st.x;
		ray.y = cub.per.st.y;
		depth_of_field = 8;
	}
	// printf("HORI_Ray   Off_X%f Off_Y%f\n", ray.x_offset, ray.y_offset);
	while (depth_of_field < 8)
	{
		// divided or multi
		map_x = (int)(ray.x) >> 6;
		map_y = (int)(ray.y) >> 6;
		if (map_y >= 0 && map_y < (int)cub.map.map_line_max && map_x >= 0 && map_x < (int)cub.map.map_column_max &&
			cub.map.a_map[map_y][map_x] == '1')
			depth_of_field = 8;
		else
		{
			ray.x += ray.x_offset;
			ray.y += ray.y_offset;
			depth_of_field++;
		}
	}
	// printf("MAPX %d   MAPY %d\n", map_x, map_y);
	ray.distance_per = pythagoras(cub.per.st.x, cub.per.st.y, ray.x, ray.y);
	// printf("PX%f  PY%f   RX%f  RY%f\n", cub.per.st.x, cub.per.st.y, ray.x, ray.y);
	return (ray);
}

void	draw_walls(t_all cub, int x, t_raycaster wall_ray)
{
	int	line_h;
	int line_offset;

	line_h = 64 * HEIGHT / wall_ray.distance_per;
	if (line_h > HEIGHT)
		line_h = HEIGHT;
	line_offset = HEIGHT/2 - line_h / 2;
	while (line_h >= 0)
	{
		// printf("X%d  Y%d\n", x, line_h);
		if ((x >= 0 && x < WIDTH) && (line_h + line_offset >= 0 && line_h + line_offset < HEIGHT))
			mlx_put_pixel(cub.image_game, x, line_h + line_offset, 0x000000FF);
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
	// DDA(cub.per.pos.x * 64, cub.per.pos.y * 64,
	// 		cub.per.pos.x * 64 + 20 * cos(cub.per.direction),
	// 		cub.per.pos.y * 64 + 20 * sin(cub.per.direction),
	// 	cub);
	double	angle_add;

	// for (int i = 0; i < WIDTH; i++)
	// 	mlx_put_pixel(cub.image_player, i, 320, 0xFFFFFFF);
	// for (int i = 0; i < HEIGHT; i++)
	// 	mlx_put_pixel(cub.image_player, 320, i, 0xFFFFFFF);
	angle_add = 0;
	t_raycaster rays[2];
	// printf("direction [%f] | angle_add [%f]\n", cub.per.direction, angle_add);
	cub.per.direction = (cub.per.angle_real / 180 * PI) - cub.per.fov / 2;
	// cub.per.direction = ;
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
		if (rays[0].distance_per < rays[1].distance_per)
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
}

/* ************************************************************************** */
