/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:28:02 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 17:41:26 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	correct_player(t_elm_map *map)
{
	t_txt	result;
	t_txt	first;
	t_txt	second;

	first.x = round_base(map->p_x);
	second.x = round_base(map->p_x + PSIZE);
	first.y = round_base(map->p_y);
	second.y = round_base(map->p_y + PSIZE);
	result.x = first.x;
	if (first.x > second.x)
		result.x = second.x;
	result.y = first.y;
	if (first.y > second.y)
		result.y = second.y;
	map->p_x = result.x;
	map->p_y = result.y;
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

void	move_player(t_elm_map *map, char dir, double extra)
{
	float		rads;
	float		x;
	float		y;
	double		degrees;
	double		offset;

	degrees = 0;
	if (dir == 'w')
		degrees = map->dir;
	else if (dir == 's')
		degrees = map->dir + 180;
	else if (dir == 'a')
		degrees = map->dir + 90;
	else if (dir == 'd')
		degrees = map->dir + 270;
	offset = (sqrt(BSIZE) * 4 * sqrt(2)) / 2;
	rads = deg2rad(degrees + extra);
	x = sin(rads) * offset + map->p_x;
	y = cos(rads) * offset + map->p_y;
	check_and_correct(map, x, y);
	draw_3d(map);
}

void	change_dir(t_elm_map *map, char c, int move)
{
	if (map->dir == 0 && c == 'r')
		map->dir = 355;
	else if (map->dir == 360 && c == 'l')
		map->dir = move;
	else
		map->dir += move;
	draw_3d(map);
}

int	events(int key, t_elm_map	*map)
{
	if (key == W)
		move_player(map, 'w', 0);
	if (key == S)
		move_player(map, 's', 0);
	if (key == D)
		move_player(map, 'd', 0);
	if (key == A)
		move_player(map, 'a', 0);
	if (key == CAMERA_R)
		change_dir(map, 'r', -2);
	if (key == CAMERA_L)
		change_dir(map, 'l', 2);
	if (key == ESC)
		exit(1);
	return (1);
}
