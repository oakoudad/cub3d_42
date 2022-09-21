/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:17:23 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/21 23:23:32 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_block(int y, int x, t_elm_map	*map, int color)
{
	int	j;
	int	i;

	j = y * BSIZE;
	while (j < (y * BSIZE) + BSIZE)
	{
		i = x * BSIZE;
		while (i < (x * BSIZE) + BSIZE)
		{
			my_mlx_pixel_put(&map->m_mlx.img, i, j, color);
			i++;
		}
		j++;
	}
}

void	put_player_block(int y, int x, t_elm_map *map, int color)
{
	int	j;
	int	start;
	int	inc;
	int	sig;
	int	i;

	j = y;
	sig = 1;
	inc = 2;
	start = PSIZE % 2;
	if (start == 0)
		start = 2;
	while (j < (y) + PSIZE)
	{
		i = x;
		while (i < (x) + PSIZE)
		{
			if (i - x >= (PSIZE - inc) / 2 && i - x < (PSIZE - inc) / 2 + inc)
				my_mlx_pixel_put(&map->m_mlx.img, i, j, color);
			i++;
		}
		printf("\n");
		j++;
		if (j - y == PSIZE / 2)
			sig = -1;
		else
			inc += 2 * sig;
	}
}

void	draw_map_2d(t_elm_map	*map)
{
	int	y;
	int	x;

	y = 1;
	while (map->map[y] && y <= map->line_nbr)
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '1')
				put_block(y - 1, x, map, 0x333333);
			else if (map->map[y][x] == '0')
				put_block(y - 1, x, map, 0x777777);
			x++;
		}
		y++;
	}
}

int	draw_line(t_elm_map *map, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		if ((int)pixelY / BSIZE > 0 && (int)pixelY / BSIZE < map->line_nbr && map->map[((int)pixelY / BSIZE) + 1][(int)pixelX / BSIZE] == '0')
			my_mlx_pixel_put(&map->m_mlx.img, pixelX, pixelY, color);
		else
			return 0;
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

void	draw_2d(t_elm_map *map)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int i;

	draw_map_2d(map);
	start_x = map->p_x + PSIZE / 2;
	start_y = map->p_y + PSIZE / 2;
	i = -30;
	while(i >= -30 && i <= 30)
	{
		end_x = sin(deg2rad(map->dir + i)) * 5000 + start_x;
		end_y = cos(deg2rad(map->dir + i)) * 5000 + start_y;
		draw_line(map, start_x, start_y, end_x, end_y, 0x88FF88);
		i += 1;
	}
	put_player_block(map->p_y, map->p_x, map, 0x0000FF);
	mlx_put_image_to_window(map->m_mlx.mlx, map->m_mlx.win,
		map->m_mlx.img.img, 0, 0);
}

void	move_player(t_elm_map *map, int move, char dir)
{
	int	next;

	if (dir == 'y')
	{
		next = map->p_y + move;
		if (map->map[(next / BSIZE) + 1][map->p_x / BSIZE] == '0')
			map->p_y = next;
	}
	else if(dir == 'x')
	{
		next = map->p_x + move;
		if (map->map[(map->p_y / BSIZE) + 1][next / BSIZE] == '0')
			map->p_x = next;
	}
	draw_2d(map);
}

void    change_dir(t_elm_map	*map, char c, int move)
{
	if (map->dir == 0 && c == 'r')
		map->dir = 355;
	else if (map->dir == 360 && c == 'l')
		map->dir = move;
	else
		map->dir += move;
	printf("{%d}\n", map->dir);
	draw_2d(map);
}

int	events(int key, t_elm_map	*map)
{
	if (key == 13 || key == 0 || key == 5 || key == 1)
		mlx_clear_window(map->m_mlx.mlx, map->m_mlx.win);
	if (key == 13)
		move_player(map, -PSIZE, 'y');
	if (key == 1)
		move_player(map, PSIZE, 'y');
	if (key == 2)
		move_player(map, PSIZE, 'x');
	if (key == 0)
		move_player(map, -PSIZE, 'x');
	if (key == 124)
		change_dir(map, 'r', -5);
	if (key == 123)
		change_dir(map, 'l', 5);
	return (1);
}

void	raycasting_main(t_elm_map	*map)
{
	int		i;
	int		j;

	map->m_mlx.mlx = mlx_init();
	map->m_mlx.win = mlx_new_window(map->m_mlx.mlx,
			map->longer_line * BSIZE,
			(map->line_nbr) * BSIZE, "Hello world!");
	map->m_mlx.img.img = mlx_new_image (map->m_mlx.mlx, map->longer_line * BSIZE,
			(map->line_nbr) * BSIZE);
	map->m_mlx.img.addr = mlx_get_data_addr (map->m_mlx.img.img,
			&map->m_mlx.img.bits_per_pixel, &map->m_mlx.img.line_length,
			&map->m_mlx.img.endian);
	printf("{current dir = %d}\n", map->dir);
	draw_2d(map);
	mlx_hook(map->m_mlx.win, 2, (2L << 0), events, map);
	mlx_loop(map->m_mlx.mlx);
}
