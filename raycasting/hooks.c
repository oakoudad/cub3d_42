/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:28:02 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/17 18:14:11 by oakoudad         ###   ########.fr       */
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
	if (is_wall_or_space((int)x1 / BSIZE, (int)y1 / BSIZE, map))
		status = 0;
	if (is_wall_or_space((int)x2 / BSIZE, (int)y1 / BSIZE, map))
		status = 0;
	if (is_wall_or_space((int)x1 / BSIZE, (int)y2 / BSIZE, map))
		status = 0;
	if (is_wall_or_space((int)x2 / BSIZE, (int)y2 / BSIZE, map))
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
	offset = (sqrt(BSIZE) * SPEED * sqrt(2)) / 2;
	rads = deg2rad(degrees + extra);
	x = sin(rads) * offset + map->p_x;
	y = cos(rads) * offset + map->p_y;
	check_and_correct(map, x, y);
	draw_3d(map);
}

void	change_dir(t_elm_map *map, char c, float move)
{
	if (map->dir == 0 && c == 'r')
		map->dir = 355;
	else if (map->dir == 360 && c == 'l')
		map->dir = move;
	else
		map->dir += move;
	draw_3d(map);
}

int	events(t_elm_map	*map)
{
	if (map->keys.vrt == 1)
		move_player(map, 'w', 0);
	if (map->keys.vrt == -1)
		move_player(map, 's', 0);
	if (map->keys.hor == -1)
		move_player(map, 'd', 0);
	if (map->keys.hor == 1)
		move_player(map, 'a', 0);
	if (map->keys.cam == 1)
		change_dir(map, 'r', -3);
	else if (map->keys.cam == -1)
		change_dir(map, 'l', 3);
	return (1);
}
