/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:22:13 by oakoudad          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/21 14:09:00 by oakoudad         ###   ########.fr       */
=======
/*   Updated: 2022/09/21 14:03:00 by eelmoham         ###   ########.fr       */
>>>>>>> 2905e78d582fae1b0550eea1bb89c394fa6a262e
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_img;

void	init_struct(t_elm_map	*map)
{
	map->texture_fd[NO] = -1;
	map->texture_fd[SO] = -1;
	map->texture_fd[WE] = -1;
	map->texture_fd[EA] = -1;
	map->floor.r = -1;
	map->floor.g = -1;
	map->floor.b = -1;
	map->ceiling.r = -1;
	map->ceiling.g = -1;
	map->ceiling.b = -1;
	map->line_nbr = 0;
	map->longer_line = 0;
	map->player = 0;
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
	t_elm_map	map;

	init_struct(&map);
	check_inputs(ac, av);
	read_file(av[1], &map);
	if (!init_map(av[1], &map))
		return (0);
	check_map(&map);
	
	// raycasting >>
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	int i = 0 , j = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, map.longer_line*10, (map.line_nbr + 2) * 10, "Hello world!");
	img.img = mlx_new_image(mlx, map.longer_line*10, (map.line_nbr + 2) * 10);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	int y = 1;
	int x = 0;
	
	while (map.map[y])
	{
		x = 0;
		while (map.map[y][x])
		{
			if (map.map[y][x] == '1')
			{
				j = y * 10;
				while (j < (y * 10) + 10)
				{
					i = x * 10;
					while (i < (x * 10) + 10)
					{
						my_mlx_pixel_put(&img, i, j, 0x00FF0000);
						i++;
					}
					j++;
				}
			}
			x++;
		}
		y++;
		
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
