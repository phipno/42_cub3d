
#include "MLX42.h"
#include "cub3d.h"
#include "cub_minimap.h"

#define START_X 0
#define START_Y 0
#define END_X 150
#define END_Y 150

int	main(void)
{
	t_minimap	minimap;
	t_vec_pos 	start;
	t_vec_pos 	end;

	start.x = START_X;
	start.y = START_Y;
	end.x = END_X;
	end.y = END_Y;

	// DEBUG
	minimap_print(DEBUG_FD, &minimap);
	vec_pos_print(DEBUG_FD, "start", &start);
	vec_pos_print(DEBUG_FD, "end", &end);

	minimap_init(&minimap, start, end);

	// MLX
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	image = mlx_new_image(mlx, 250, 250);
	
	mlx_image_to_window(mlx, image, 0, 0);

	// Drawing
	minimap_draw(image, &start, &end);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
