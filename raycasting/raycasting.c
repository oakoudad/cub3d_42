/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:17:23 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/12 01:41:35 by eelmoham         ###   ########.fr       */
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

void	rsaaam(t_elm_map *map, float wall_x, float wall_y, float i, float dilta, int v)
{
	float			h;
	float			distance;
	int				x;
	int				y;
	unsigned int	xcolor;

	x = 0;
	y = 0;
	
	(void)v;
	float	deltaX;
	deltaX = wall_x - map->p_x;
	float	deltaY;
	deltaY = wall_y - map->p_y;

	distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	distance = cos(deg2rad(dilta)) * fabs(distance);
	(void)dilta;
	
	h =  HSCREEN * BSIZE / (distance);
	float	yy = 0;
	float	to = (HSCREEN - h) / 2;
	while (yy >= 0 && yy < to && yy < HSCREEN)
		my_mlx_pixel_put(&map->m_mlx.img3d, (i), (yy++), 0x9999ff);
	int x_offset = 0;
	int y_offset = 0;
	while (yy >= to && yy < to + h && yy < HSCREEN)
	{
		// if (v == 1)
		// 	x = (int)(wall_y) % BSIZE;
		// else
		// 	x = (int)(wall_x) % BSIZE;
		// y = (yy - to) * (BSIZE / h);
		y_offset = ((float)wall_y / h) * map->txtimg.height;
		x_offset = (int)wall_x % map->txtimg.width;
		xcolor = create_texture(x_offset, y_offset, map, h);
		my_mlx_pixel_put(&map->m_mlx.img3d, (i), (yy++), xcolor);
	}
	while (yy < HSCREEN)
		my_mlx_pixel_put(&map->m_mlx.img3d, (i), (yy++), 0x555555);
}



int	draw_line(t_elm_map *map, float endX, float endY)
{
	float	deltaX;
	float	deltaY;
	int	pixels;

	deltaX = endX - map->p_x;
	deltaY = endY - map->p_y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	endX = map->p_x;
	endY = map->p_y;
	while (pixels && endY / BSIZE >= 0 && endX / BSIZE >= 0 && endX / BSIZE <= map->longer_line && endY / BSIZE <= map->line_nbr)
	{
		if (map->map[((int)endY / BSIZE)][(int)endX / BSIZE] == '0')
			my_mlx_pixel_put(&map->m_mlx.img, endX, endY, 0xffffff);
		else if (map->map[((int)endY / BSIZE)][(int)endX / BSIZE] == '1')
		{
			my_mlx_pixel_put(&map->m_mlx.img, endX, endY, 0xff0000);
		}
		endX += deltaX;
		endY += deltaY;
		--pixels;
	}
	return (1);
}



void	draw_2d(t_elm_map *map)
{
	float	end_x;
	float	end_y;
	float	i;
	float	j;

	draw_map_2d(map);
	i = 30;
	j = 0;
	
	while(i <= 30 && i >= -30)
	{
		end_x = sin(deg2rad(map->dir + i)) * 30 + map->p_x;
		end_y = cos(deg2rad(map->dir + i)) * 30 + map->p_y;
		draw_line(map, end_x, end_y);
		findwall(map, i, j);
		i -= .03;
		j = j + 1;
	}
	mlx_put_image_to_window(map->m_mlx.mlx, map->m_mlx.win,
		map->m_mlx.img.img, 0, 0);
	mlx_put_image_to_window(map->m_mlx.mlx, map->m_mlx.win3d,
		map->m_mlx.img3d.img, 0, 0);
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
	draw_2d(map);
}


int	events(int key, t_elm_map	*map)
{
	if (key == S || key == A || key == W || key == D
		|| key == CAMERA_L || key == CAMERA_R)
	{
		mlx_clear_window(map->m_mlx.mlx, map->m_mlx.win);
		mlx_clear_window(map->m_mlx.mlx, map->m_mlx.win3d);
	}
	if (key == W)
		move_player(map, 'w');
	if (key == S)
		move_player(map, 's');
	if (key == D)
		move_player(map, 'd');
	if (key == A)
		move_player(map, 'a');
	if (key == CAMERA_R)
		change_dir(map, 'r', -2);
	if (key == CAMERA_L)
		change_dir(map, 'l', 2);
	if (key == ESC)
		exit(1);
	return (1);
}

void	raycasting_main(t_elm_map	*map)
{
	map->m_mlx.mlx = mlx_init();
	if (!map->m_mlx.mlx)
		write(2, "mlx init return a NULL Value\n",31);
	map->m_mlx.win3d = mlx_new_window(map->m_mlx.mlx, WSCREEN, HSCREEN, "CUB3D!");
	map->m_mlx.img3d.img = mlx_new_image (map->m_mlx.mlx, WSCREEN, HSCREEN);
	map->m_mlx.img3d.addr = mlx_get_data_addr (map->m_mlx.img3d.img, &map->m_mlx.img3d.bits_per_pixel, &map->m_mlx.img3d.line_length, &map->m_mlx.img3d.endian);

	map->m_mlx.win = mlx_new_window(map->m_mlx.mlx, map->longer_line * BSIZE, (map->line_nbr) * BSIZE, "CUB3D!");
	map->m_mlx.img.img = mlx_new_image(map->m_mlx.mlx, map->longer_line * BSIZE, (map->line_nbr) * BSIZE);
	map->m_mlx.img.addr = mlx_get_data_addr(map->m_mlx.img.img, &map->m_mlx.img.bits_per_pixel, &map->m_mlx.img.line_length, &map->m_mlx.img.endian);
	
	map->txtimg.img.img =  mlx_xpm_file_to_image(map->m_mlx.mlx , "_texture/toto.xpm", &map->txtimg.width, &map->txtimg.height);
	map->txtimg.img.addr = mlx_get_data_addr(map->txtimg.img.img,&map->txtimg.img.bits_per_pixel , &map->txtimg.img.line_length, &map->txtimg.img.endian);
	// mlx_put_image_to_window(map->m_mlx.mlx, map->m_mlx.win3d, map->txtimg.img.img, 0, 0);
	// mlx_loop(map->m_mlx.mlx);
	draw_2d(map);
}
