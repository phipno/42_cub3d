/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:48:45 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/21 12:52:04 by pnolte           ###   ########.fr       */
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
	int depth_of_field;

	ray.dir = cub.per.direction;
	depth_of_field = 0;
	float nTan = -tan(ray.dir);
	if (ray.dir > P2 && ray.dir < P3)
	{
		ray.x = (((int)cub.per.d_pos.x >> 6) << 6) - 0.0001;
		ray.y = (cub.per.d_pos.x - ray.x) * nTan + cub.per.d_pos.y;
		ray.offset.x = -64;
		ray.offset.y = -ray.offset.x * nTan;
		ray.color = 0xAAAAAAFF;
		ray.cardinal_dir = EAST;
	}
	if (ray.dir < P2 || ray.dir > P3)
	{
		ray.x = (((int)cub.per.d_pos.x >> 6) << 6) + 64;
		ray.y = (cub.per.d_pos.x - ray.x) * nTan + cub.per.d_pos.y;
		ray.offset.x = 64;
		ray.offset.y = -ray.offset.x * nTan;
		ray.color = 0x0000AAFF;
		ray.cardinal_dir = WEST;
	}
	if (ray.dir == P2 || ray.dir == P3)
	{
		ray.x = cub.per.d_pos.x;
		ray.y = cub.per.d_pos.y;
		depth_of_field = DEPTH_OF_FIELD;
		ray.color = 0x444444FF;
		//@note fixing on which side its on
		ray.cardinal_dir = SOUTH;
	}
	// printf("HORI_Ray   Off_X%f Off_Y%f\n", ray.x.offset, ray.y.offset);
	while (depth_of_field < DEPTH_OF_FIELD)
	{
		// ray.map.x = (int)(ray.x) >> 6;
		// ray.map.y = (int)(ray.y) >> 6;
		ray.map.x = ray.x / 64;
		ray.map.y = ray.y / 64;
		if (ray.map.y >= 0 && ray.map.y < (int)cub.map.map_line_max && ray.map.x >= 0 &&
		ray.map.x < (int)cub.map.map_column_max && cub.map.a_map[(int)ray.map.y][(int)ray.map.x] == '1')
			depth_of_field = DEPTH_OF_FIELD;
		else
		{
			ray.x += ray.offset.x;
			ray.y += ray.offset.y;
			depth_of_field++;
		}
	}
	// printf("MAPX %d   MAPY %d\n", map_x, map_y);
	ray.distance_raw = pythagoras(cub.per.d_pos.x, cub.per.d_pos.y, ray.x, ray.y);
	return (ray);
}

t_raycaster	draw_rays_hori(t_all cub)
{
	t_raycaster ray;
	int depth_of_field;


	ray.dir = cub.per.direction;
	depth_of_field = 0;
	float aTan = -1/tan(ray.dir);
	if (ray.dir > PI)
	{
		//looking up
		ray.y = (((int)cub.per.d_pos.y >> 6) << 6) - 0.0001;
		ray.x = (cub.per.d_pos.y - ray.y) * aTan + cub.per.d_pos.x;
		ray.offset.y = (int)-64;
		ray.offset.x = -ray.offset.y * aTan;
		ray.color = 0xAA0000FF;
		ray.cardinal_dir = SOUTH;
	}
	if (ray.dir < PI)
	{
		//looking down
		ray.y =  (((int)cub.per.d_pos.y >> 6) << 6) + 64;
		ray.x = (cub.per.d_pos.y - ray.y) * aTan + cub.per.d_pos.x;
		ray.offset.y = 64;
		ray.offset.x = -ray.offset.y * aTan;
		ray.color = 0x00AA00FF;
		ray.cardinal_dir = NORTH;
	}
	if (ray.dir == 0 || ray.dir == PI)
	{
		//looking straigt left or right
		ray.x = cub.per.d_pos.x;
		ray.y = cub.per.d_pos.y;
		depth_of_field = DEPTH_OF_FIELD;
		ray.color = 0x444444FF;
		//@note fixing on which side its on
		ray.cardinal_dir = NORTH;
	}
	// printf("HORI_Ray   Off_X%f Off_Y%f\n", ray.x.offset, ray.y.offset);
	while (depth_of_field < DEPTH_OF_FIELD)
	{
		// divided or multi
		// map_x = (int)(ray.x) >> 6;
		// map_y = (int)(ray.y) >> 6;
		ray.map.x = ray.x / 64;
		ray.map.y = ray.y / 64;
		if (ray.map.y >= 0 && ray.map.y < (int)cub.map.map_line_max && ray.map.x >= 0
		&& ray.map.x < (int)cub.map.map_column_max && cub.map.a_map[(int)ray.map.y][(int)ray.map.x] == '1')
			depth_of_field = DEPTH_OF_FIELD;
		else
		{
			ray.x += ray.offset.x;
			ray.y += ray.offset.y;
			depth_of_field++;
		}
	}
	// printf("MAPX %d   MAPY %d\n", map_x, map_y);
	ray.distance_raw = pythagoras(cub.per.d_pos.x, cub.per.d_pos.y, ray.x, ray.y);
	// printf("PX%f  PY%f   RX%f  RY%f\n", cub.per.st.x, cub.per.st.y, ray.x, ray.y);
	return (ray);
}

void	draw_walls(t_all cub, int x, t_raycaster ray)
{
	int		line_h;
	int		line_offset;
	double	angle;


	// angle fixes the distortion from walls on the same
	// grid line not being displayed on the same y height
	// in short fixes fish eye
	angle = (cub.per.angle_real / 180 * PI) - cub.per.direction;
	if (angle < 0)
		angle = angle + 2 * PI;
	if (angle > 2 * PI)
		angle = angle - 2 * PI;
	ray.distance_parralel = cos(angle) * ray.distance_raw;


	//for the offset we need to know at what pixel of a wall were
	//looking and where is the wall end. to calculate a factor so we can
	//increment it in rotational way.

	int			x_offset;
	int			y_step;
	double		y_count;


	y_count = 0;
	x_offset = 0;
	if (ray.cardinal_dir == NORTH || ray.cardinal_dir == SOUTH)
	{
		x_offset = (ray.map.x - (int)ray.map.x) / cub.map.mlx_wall[ray.cardinal_dir]->width * 4;
	}
	else if (ray.cardinal_dir == EAST || ray.cardinal_dir == WEST)
	{
		x_offset = (ray.map.y - (int)ray.map.y) / cub.map.mlx_wall[ray.cardinal_dir]->width * 4;
	}
	printf("X%d   MapX%f   MapY%f   X_Offset%d\n",x, ray.map.x, ray.map.y, (int)x_offset);
	line_h = WALL_HEIGHT * HEIGHT / ray.distance_parralel;
	if (line_h > HEIGHT)
		line_h = HEIGHT;
	line_offset = HEIGHT/2 - line_h / 2;
	while (line_h >= 0)
	{
		y_step = cub.map.mlx_wall[ray.cardinal_dir]->width * y_count;
		if ((x >= 0 && x < WIDTH) && (line_h + line_offset >= 0 && line_h + line_offset < HEIGHT
			&& 3 + y_step + x_offset < (int)cub.map.mlx_wall[ray.cardinal_dir]->width * (int)cub.map.mlx_wall[ray.cardinal_dir]->height * 4
			&& y_step + x_offset > -1))
			mlx_put_pixel(cub.image_game, x, line_h + line_offset, get_rgba(
			cub.map.mlx_wall[ray.cardinal_dir]->pixels[0 + y_step + x_offset],
			cub.map.mlx_wall[ray.cardinal_dir]->pixels[1 + y_step + x_offset],
			cub.map.mlx_wall[ray.cardinal_dir]->pixels[2 + y_step + x_offset],
			cub.map.mlx_wall[ray.cardinal_dir]->pixels[3 + y_step + x_offset]));
		y_count = (line_h + line_offset) / cub.map.mlx_wall[ray.cardinal_dir]->width;
		line_h--;
	}
	// printf("Ystep %d\n", y_count);
}

void	draw_player(t_all cub)
{
	// (void)cub;

	//printf("element.size_x [%f] element.size_y [%f]\n", cub.minimap.element.size_x, cub.minimap.element.size_y);
	cub.per.d_pos.x = cub.per.pos.x * MAP_SCALE;
	cub.per.d_pos.y = cub.per.pos.y * MAP_SCALE;
	// printf("Pos%f Pos%f\n", cub.per.pos.x, cub.per.pos.y);
	// printf("D_Pos%f D_Pos%f\n", cub.per.d_pos.x, cub.per.d_pos.y);

	// draw_map(cub);
	// for (int y = cub.per.pos.y * 64; y < cub.per.pos.y * 64 + 10; y++)
	// {
	// 	for (int x = cub.per.pos.x * 64; x < cub.per.pos.x * 64 + 10; x++)
	// 	{
	// 		mlx_put_pixel(cub.image_game, x, y, 0xFFFF55FF);
	// 	}
	// }

	float	angle_add;

	angle_add = 0.5;

	t_raycaster rays[2];
	// printf("FOV%f", fov);

	angle_add = (FOV * (PI / 180)) / WIDTH;
	cub.per.direction = (cub.per.angle_real * (PI / 180)) - (FOV * (PI / 180)) / 2;
	// printf("direction [%f] | angle_add [%f]\n", cub.per.direction, angle_add);
	// printf("FOV %D WITDH %D\n", FOV, WIDTH);
	// printf("direction [%f] | angle_add [%f]\n", cub.per.direction, angle_add);
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
			// printf("Angle [%f]  d_posX [%f]  d_posY[%f]  rX[%f]  rY[%f]\n", cub.per.direction, cub.per.d_pos.x, cub.per.d_pos.y, rays[0].x, rays[0].y);
			// DDA(cub.per.d_pos.x, cub.per.d_pos.y, rays[0].x, rays[0].y, cub, 0xFF0000FF);
			draw_walls(cub, x, rays[0]);
		}
		else
		{
			// printf("Angle [%f]  d_posX [%f] | d_posY [%f] | rX[%f] | rY[%f]\n", cub.per.direction, cub.per.d_pos.x, cub.per.d_pos.y, rays[1].x, rays[1].y);
			// DDA(cub.per.d_pos.x, cub.per.d_pos.y, rays[1].x, rays[1].y, cub, 0xFF0000FF);
			draw_walls(cub, x, rays[1]);
		}
		// DDA(cub.per.d_pos.x, cub.per.d_pos.y, cub.per.d_pos.x + 30 * cos(cub.per.angle_real / 180 * PI), cub.per.d_pos.y + 30 * sin(cub.per.angle_real / 180 * PI), cub, 0x00FF00FF);
		cub.per.direction += angle_add;
	}

	// mlx_texture_t	*wall;
	// mlx_image_t		*i;

	// wall = mlx_load_png(cub.map.north_wall);
	// i = mlx_texture_to_image(cub.mlx, wall);
	// mlx_image_to_window(cub.mlx, i, 300, 300);

}

/* ************************************************************************** */
