/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:17:23 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/29 14:29:45 by eelmoham         ###   ########.fr       */
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

void	rsaaam(t_elm_map *map, float wall_x, float wall_y, float i, float dilta)
{
	puts("fbdfbadb\n");
	float	h;
	float	distance;
	
	float	deltaX;
	deltaX = wall_x - map->p_x;
	float	deltaY;
	deltaY = wall_y - map->p_y;

	distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	//distance = fabs(cos(deg2rad(map->dir) - deg2rad(dilta))) * distance;
	(void)dilta;
	//distance = sqrt((distance * distance) - (a * a));
	
	h =  HSCREEN * 5 / (distance);
	//((distance * BSIZE) / map->line_nbr);
	float	yy = 0;
	//float	to = (HSCREEN - h)/2;
	float	to = (HSCREEN - h) / 2;
	while (yy >= 0 && yy < to && yy < HSCREEN)
		my_mlx_pixel_put(&map->m_mlx.img3d, (i), (yy++), 0xAAAAFF);
	while (yy >= to && yy < to + h && yy < HSCREEN)
		my_mlx_pixel_put(&map->m_mlx.img3d, (i), (yy++), 0xcccccc);
	while (yy < HSCREEN)
		my_mlx_pixel_put(&map->m_mlx.img3d, (i), (yy++), 0xaaddaa);
}

int	draw_line(t_elm_map *map, float endX, float endY, float i, float dilta)
{
	float	deltaX;
	float	deltaY;
	float	pixels;

	deltaX = endX - map->p_x;
	deltaY = endY - map->p_y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	endX = map->p_x;
	endY = map->p_y;
	while (pixels && endY / BSIZE >= 0 && endX / BSIZE >= 0 && endX / BSIZE <= map->longer_line && endY / BSIZE <= map->line_nbr)
	{
		if (map->map[((int)endY / BSIZE)][(int)endX / BSIZE] == '0'){
			my_mlx_pixel_put(&map->m_mlx.img, endX, endY, 0xffffff);
		}
		else
		{
			rsaaam(map, endX, endY, i, dilta);
			return (my_mlx_pixel_put(&map->m_mlx.img, endX, endY, 0xff0000), 0);
		}
		endX += deltaX;
		endY += deltaY;
		--pixels;
	}
	return (1);
}

/*
ay = [py/BSIZE]*BSIZE
ax = px + (py - ay)/tan(angel)
ystep = BSIZE
xstep = ystep/tan(angel);
	angel = 
	
	// ystep = BSIZE;
	// xstep = BSIZE/tan(rad2deg(map->dir));
*/

float dist(t_elm_map *map, float endX, float endY)
{
	float	deltaX;
	float	deltaY;
	float	dst;
	
	deltaX = endX - map->p_x;
	deltaY = endY - map->p_y;
	dst = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	return (dst);
}


// float normalaize_angel(float angel)
// {
// 	angel /= (2 * M_PI);

// 	if (angel < 0)
// 		return(angel + (2 * M_PI));
// 	return (angel);
// }

// int up_down(float angel)
// {
// 	int face;
// 	if (angel > 0 && angel < M_PI)
// 		face = -1;//down
// 	else
// 		face = 1;//up
// 	if ()
// }

// float	find_wall(t_elm_map *map, float angel, int i)
// {
	
// 	float hzfx;
// 	float hzfy;
// 	float vrfx;
// 	float vrfy;
// 	(void)i;
// 	printf("angel is %f\n", angel + map->dir);
// 	// angel = normalaize_angel(deg2rad(angel + map->dir));
// 	printf("angel is %f\n", angel);
// 	//first horizontal intersection
// 	hzfy = floor(map->p_y / BSIZE) * BSIZE; 
// 	//printf("%f\n\n\n", hzfy);
// 	if (angel > 0 && angel < M_PI)
// 		hzfy+=BSIZE;
// 	hzfx = PX + ((PY - hzfy)/tan(deg2rad(angel)));
	
// 	//first vertical intersection
// 	vrfx =  floor(map->p_x /10) * 10;
// 	vrfy = PX + ((PY - vrfx)/tan(deg2rad(angel)));
	
	
// 	// printf("is wall %d\n", is_wall(map, hzfy, hzfx));
// 	// printf("%f, %f \n", hzfy, hzfx);
// 	// printf("%f, %f \n", PY, PY);
// 	while(1)
// 	{
// 		if (is_wall(map, hzfy, hzfx) == 1 || is_wall(map, vrfy, vrfx) == 1) // || is_wall(map, vrfy, vrfx) == 1
// 		{
// 			if (dist(map, hzfy, hzfx) <= dist(map, vrfy, vrfx))
// 			{
// 				printf("%f %f %f\n", angel,hzfx,hzfy);
// 				rsaaam(map, hzfx, hzfy, angel, 0);
// 				exit(1);
// 				return (dist(map, hzfy, hzfx));
// 			}
// 			else if (dist(map, hzfy, hzfx) > dist(map, vrfy, vrfx))
// 			{
// 				rsaaam(map, vrfx, vrfy, i, 0);
// 				return (dist(map, vrfy, vrfx));
// 			}
// 		}
// 		else
// 		{
// 			hzfy += BSIZE;
// 			hzfx += hzfy / tan(deg2rad(map->dir + angel));
// 			vrfx += BSIZE;
// 			vrfy += vrfx / tan(deg2rad(map->dir + angel));
// 		}
// 	}
// 	return (-1);
// }

int is_wall(t_elm_map *map, int x, int y)
{
	puts("cc\n");
	printf("x >>>%d >>>>>%d\n", x, y);
	if (y / BSIZE >= 0  && y / BSIZE < map->line_nbr && x / BSIZE >= 0 && x / BSIZE <= map->longer_line && map->map[y/BSIZE][x/BSIZE] == '1')
	{
		puts("vu1\n");
		return (1);
	}
	else
	{
		puts("vu2\n");
		return (0);
	}
	puts("read!\n");
	return (-1);
}

float	correct_angle(float angle)
{
	if (angle > 360)
		return (angle - 360);
	if (angle < 0)
		return (360 + angle);
	return (angle);
}

float	find_wall2(t_elm_map *map , float angle, float x)
{
	float	h_wall_x = 0;
	float	h_wall_y = 0;
	float	v_wall_x;
	float	v_wall_y;
	int		h = -1;
	int		v = -1;
	
	(void)x;
	angle = correct_angle(map->dir + angle);
	if ((angle >= 270 && angle <= 360) || (angle >= 0 && angle < 90))
		v = 1;
	if (!(angle > 180 && angle < 360))
		h = 1;
	v_wall_y = floor(map->p_y / BSIZE) * BSIZE;
	if (v == 1)
		v_wall_y += BSIZE;
	v_wall_x = map->p_x + v * (fabs(map->p_y - v_wall_y) * tan(deg2rad(angle)));
	

	h_wall_x = floor(map->p_x / BSIZE) * BSIZE;
	if (h == 1)
		h_wall_x += BSIZE;
	h_wall_y = map->p_y + h * (fabs(map->p_x - h_wall_x) * tan(deg2rad(90 - angle)));
	if (h_wall_y / BSIZE >= 0  && h_wall_y / BSIZE < map->line_nbr && h_wall_x / BSIZE >= 0 && h_wall_x / BSIZE <= map->longer_line)
		my_mlx_pixel_put(&map->m_mlx.img, h_wall_x, h_wall_y, 0xff0000);
	if (v_wall_y / BSIZE >= 0  && v_wall_y / BSIZE < map->line_nbr && v_wall_x / BSIZE >= 0 && v_wall_x / BSIZE <= map->longer_line)
		my_mlx_pixel_put(&map->m_mlx.img, v_wall_x, v_wall_y, 0x00ff00);// green, verticale
	while (1)
	{
		if (is_wall(map, (int)h_wall_y, (int)h_wall_x) == 1 || is_wall(map, (int)v_wall_y, (int)v_wall_x) == 1)
		{
			if (dist(map, h_wall_y, h_wall_x) <= dist(map, v_wall_y, v_wall_x))
			{
				rsaaam(map, h_wall_x, h_wall_y, angle, 0);
				return(dist(map, h_wall_y, h_wall_x));
			}
			else
			{
				rsaaam(map, v_wall_x, v_wall_y, angle, 20);
				return(dist(map, v_wall_y, v_wall_x));
			}
		}
		else
		{
			if (angle >= 180 && angle <= 270)
			{
				v_wall_y -= BSIZE;
				h_wall_x += BSIZE;
				h_wall_y -= BSIZE;
				v_wall_x += BSIZE;
			}
			else if (angle >= 90 && angle <= 180)
			{
				v_wall_y -= BSIZE;
				h_wall_x -= BSIZE;
				h_wall_y -= BSIZE;
				v_wall_x -= BSIZE;
			}
			else if (angle >= 270 && angle <= 360)
			{
				v_wall_y += BSIZE;
				h_wall_x += BSIZE;
				h_wall_y += BSIZE;
				v_wall_x += BSIZE;
			}
			else if (angle <= 90 && angle >= 0)
			{
				v_wall_y += BSIZE;
				h_wall_x += BSIZE;
				h_wall_y += BSIZE;
				v_wall_x += BSIZE;
			}
		}
	}
	
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
		// printf("===> %f\n", map->dir + i);
		// find_wall(map , i, j);
		(void)end_x;
		(void)end_y;
		end_x = sin(deg2rad(map->dir + i)) * 1000000 + map->p_x;
		end_y = cos(deg2rad(map->dir + i)) * 1000000 + map->p_y;
		draw_line(map, end_x, end_y, j, i);
		find_wall2(map , i, 0);
		i -= .03;
		j = j + 1;
	}
	printf("%f\n", j);
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
	printf("{%d}\n", map->dir);
	draw_2d(map);
}


int	events(int key, t_elm_map	*map)
{
	printf("%d\n", key);
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
	
	map->m_mlx.win3d = mlx_new_window(map->m_mlx.mlx, WSCREEN, HSCREEN, "CUB3D!");
	map->m_mlx.img3d.img = mlx_new_image (map->m_mlx.mlx, WSCREEN, HSCREEN);
	map->m_mlx.img3d.addr = mlx_get_data_addr (map->m_mlx.img3d.img, &map->m_mlx.img3d.bits_per_pixel, &map->m_mlx.img3d.line_length, &map->m_mlx.img3d.endian);

	map->m_mlx.win = mlx_new_window(map->m_mlx.mlx, map->longer_line * BSIZE, (map->line_nbr) * BSIZE, "CUB3D!");
	map->m_mlx.img.img = mlx_new_image(map->m_mlx.mlx, map->longer_line * BSIZE, (map->line_nbr) * BSIZE);
	map->m_mlx.img.addr = mlx_get_data_addr(map->m_mlx.img.img, &map->m_mlx.img.bits_per_pixel, &map->m_mlx.img.line_length, &map->m_mlx.img.endian);

	
	

	draw_2d(map);
}
