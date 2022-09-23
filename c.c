# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <mlx.h>

typedef struct my_hook
{
	char	x;
	char	y;
	char	cam;
}	t_hook;

# define W 13
# define D 2
# define S 1
# define A 0
# define CAMERA_R 124
# define CAMERA_L 123

int release(int key, t_hook	*map)
{
	if (key == W || key == S)
		map->x = 0;
	if (key == A || key == D)
		map->y = 0;
	if (key == CAMERA_L || key == CAMERA_L)
		map->cam = 0;
    return 0;
}

int keyPress(int key, t_hook	*map)
{
	if (key == W)
		map->x = 'W';
	if (key == S)
		map->x = 'S';
	if (key == D)
		map->y = 'D';
	if (key == A)
		map->y = 'A';
	if (key == CAMERA_R)
		map->cam = 'R';
	if (key == CAMERA_L)
		map->cam = 'L';
	printf("X = %c, Y = %c, cam = %c\n", map->x, map->y, map->cam);
    return 0;
}

int main()
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	t_hook	map;

	map.x = 0;
	map.y = 0;
	map.cam = 0;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 100, "CUB3D!");
	img = mlx_new_image (mlx, 1000, 100);
	addr = mlx_get_data_addr (img, &bits_per_pixel, &bits_per_pixel, &bits_per_pixel);

	mlx_hook(win, 3, (1L << 3), release, &map);
	mlx_hook(win, 2, (1L << 0), keyPress, &map);
	mlx_loop(mlx);
}