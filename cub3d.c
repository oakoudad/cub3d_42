/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:31:05 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/21 14:48:58 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

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
	mlx_win = mlx_new_window(mlx, map.longer_line*30, (map.line_nbr + 2) * 30
		, "Hello world!");
	img.img = mlx_new_image(mlx, map.longer_line*30, (map.line_nbr + 2) * 30);
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
				put_block(y, x, &img, 0xFF0000);
			else if (map.map[y][x] == '0')
				put_block(y, x, &img, 0xFFFFFF);
			x++;
		}
		y++;
	}
	put_player_block(map.p_y, map.p_x, &img, 0x0000FF);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

void	put_block(int y, int x, t_img	*img, int color)
{
	int	j;
	int	i;

	j = y * 30;
	while (j < (y * 30) + 30)
	{
		i = x * 30;
		while (i < (x * 30) + 30)
		{
			my_mlx_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	put_player_block(int y, int x, t_img	*img, int color)
{
	int	j;
	int	i;

	j = y * 30;
	while (j < (y * 30) + 5)
	{
		i = x * 30;
		while (i < (x * 30) + 5)
		{
			my_mlx_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
}
