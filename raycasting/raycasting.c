/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:17:23 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/23 18:34:09 by oakoudad         ###   ########.fr       */
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
	my_mlx_pixel_put(&map->m_mlx.img, x, y, color);
}

void	draw_map_2d(t_elm_map	*map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y] && y < map->line_nbr)
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '1')
				put_block(y, x, map, 0x333333);
			else if (map->map[y][x] == '0')
				put_block(y, x, map, 0x777777);
			x++;
		}
		y++;
	}
}

int	draw_line(t_elm_map *map, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int status;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels;
	deltaY /= pixels;
	status = 1;
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels && pixelY / BSIZE >= 0 && pixelX / BSIZE >= 0 && pixelX / BSIZE <= map->longer_line && pixelY / BSIZE <= map->line_nbr)
	{
		if (status && map->map[((int)pixelY / BSIZE)][(int)pixelX / BSIZE] == '0')
			my_mlx_pixel_put(&map->m_mlx.img, pixelX, pixelY, color);
		else
			return 0;
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (1);
}

void	draw_2d(t_elm_map *map)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	float i;

	draw_map_2d(map);
	start_x = map->p_x;
	start_y = map->p_y;
	i = -30;
	while(i >= -30 && i <= 30)
	{
		end_x = sin(deg2rad(map->dir + i)) * 10000 + start_x;
		end_y = cos(deg2rad(map->dir + i)) * 10000 + start_y;
		draw_line(map, start_x, start_y, end_x, end_y, 0xEEEEEE);
		i += 0.1;
	}
	put_player_block(map->p_y, map->p_x, map, 0xFFFFFF);
	mlx_put_image_to_window(map->m_mlx.mlx, map->m_mlx.win,
		map->m_mlx.img.img, 0, 0);
}

int	round_base(int nbr)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((nbr + i) % PSIZE != 0)
		i++;
	while ((nbr - j) % PSIZE != 0)
		j++;
	if (i < j)
		return (nbr + i);
	else
		return (nbr - j);
}

void	correct_player(t_elm_map *map)
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	float	x2;
	float	y2;

	x1 = round_base(map->p_x);
	x2 = round_base(map->p_x + PSIZE);
	y1 = round_base(map->p_y);
	y2 = round_base(map->p_y + PSIZE);
	x = x1;
	if (x1 > x2)
		x = x2;
	y = y1;
	if (y1 > y2)
		y = y2;
	map->p_x = x;
	map->p_y = y;
}

void	check_and_correct(t_elm_map *map, float x1, float y1)
{
	float	x2;
	float	y2;
	int		status;

	status = 1;
	x2 = x1 + PSIZE;
	y2 = y1 + PSIZE;
	if ((map->map[(int)y1 / BSIZE][(int)x1 / BSIZE]) == '1')
		status = 0;
	if ((map->map[(int)y1 / BSIZE][(int)x2 / BSIZE]) == '1')
		status = 0;
	if ((map->map[(int)y2 / BSIZE][(int)x1 / BSIZE]) == '1')
		status = 0;
	if ((map->map[(int)y2 / BSIZE][(int)x2 / BSIZE]) == '1')
		status = 0;
	if (status == 0)
		correct_player(map);
	else if (status == 1)
	{
		map->p_x = x1;
		map->p_y = y1;
	}
}

void	move_player(t_elm_map *map, char dir)
{
	float rads;
	float x;
	float y;
	double degrees;
	double offset;

	degrees = 0;
	if (dir == 'w')
		degrees = map->dir;
	else if (dir == 's')
		degrees = map->dir + 180;
	else if (dir == 'a')
		degrees = map->dir + 90;
	else if (dir == 'd')
		degrees = map->dir + 270;
	offset = ((PSIZE * 3) * sqrt(2)) / 2;
	rads = deg2rad(degrees);
	x = sin(rads) * offset + map->p_x;
	y = cos(rads) * offset + map->p_y;
	check_and_correct(map, x, y);
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
	printf("%d\n", key);
	if (key == S || key == A || key == W || key == D
		|| key == CAMERA_L || key == CAMERA_R)
		mlx_clear_window(map->m_mlx.mlx, map->m_mlx.win);
	if (key == W)
		move_player(map, 'w');
	if (key == S)
		move_player(map, 's');
	if (key == D)
		move_player(map, 'd');
	if (key == A)
		move_player(map, 'a');
	if (key == CAMERA_R)
		change_dir(map, 'r', -5);
	if (key == CAMERA_L)
		change_dir(map, 'l', 5);
	if (key == ESC)
		exit(1);
	return (1);
}

void	raycasting_main(t_elm_map	*map)
{
	map->m_mlx.mlx = mlx_init();
	map->m_mlx.win = mlx_new_window(map->m_mlx.mlx,
			map->longer_line * BSIZE,
			(map->line_nbr) * BSIZE, "CUB3D!");
	map->m_mlx.img.img = mlx_new_image (map->m_mlx.mlx, map->longer_line * BSIZE,
			(map->line_nbr) * BSIZE);
	map->m_mlx.img.addr = mlx_get_data_addr (map->m_mlx.img.img,
			&map->m_mlx.img.bits_per_pixel, &map->m_mlx.img.line_length,
			&map->m_mlx.img.endian);
	draw_2d(map);
	mlx_hook(map->m_mlx.win, 2, (1L << 0), events, map);
	mlx_loop(map->m_mlx.mlx);
}