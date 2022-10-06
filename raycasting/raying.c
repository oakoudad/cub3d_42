/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raying.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:49:48 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/06 23:02:11 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int is_wall(t_elm_map *map, float x, float y)
{
	if ((int)(y / BSIZE) < 0  || (int)(y / BSIZE) >= map->line_nbr)
		return (1);
	if ((int)(x / BSIZE) < 0 || (int)(x / BSIZE) >= map->longer_line)
		return (1);
	if (map->map[(int)(y / BSIZE)][(int)(x / BSIZE)] == '0')
		return (0);
	return (1);
}

int dstwalldraw(t_elm_map *map,t_raying *r,float xv, float yv, float xh, float yh, int x)
{
	float distv;
	float disth;

	distv = -1;
	disth = -1;
	x = 0;
	printf("%f %f %f %f %f\n", xv, yv, xh, yh, r->angl);
	if (is_wall(map, xv, yv) == 1)
		puts("yes its a wall\n");
	else
		puts("omar zamel\n");
	return (-1);
}

float	correct_angle(float angle)
{
	if (angle > 360)
		return (angle - 360);
	if (angle == 0)
		return (360);
	if (angle < 0)
		return (360 + angle);
	return (angle);
}





void	findwall(t_elm_map *map, float angle, float x)
{
	t_raying raying;

	raying.vrt = 1;
	raying.hor = 1;
	raying.angl = angle;
	angle = correct_angle(map->dir + angle);
	// printf("{%f}\n", angle);
	if ((angle > 270 && angle <= 360) || (angle >= 0 && angle < 90))
		raying.vrt  = -1;
	else if (angle == 270 || angle == 90)
		raying.vrt  = 0;
	if ((angle > 0 && angle < 180))
		raying.hor = -1;
	else if (angle == 0 || angle == 360 || angle == 180)
		raying.hor  = 0;
	
	// first point V
	raying.v_wall_y = floor(map->p_y / BSIZE) * BSIZE;
	if (raying.vrt == -1)
		raying.v_wall_y += BSIZE;
	raying.v_wall_x = map->p_x + -raying.vrt * (fabs(map->p_y - raying.v_wall_y) * tan(deg2rad(angle)));
	
	
	
	// first point H
	raying.h_wall_x = floor(map->p_x / BSIZE) * BSIZE;
	if (raying.hor == -1)
		raying.h_wall_x += BSIZE;
	raying.h_wall_y = map->p_y + -raying.hor * (fabs(map->p_x - raying.h_wall_x) * tan(deg2rad(90 - angle)));

	while(1 && raying.vrt != 0)
	{
		puts("here");
		if (is_wall(map, raying.v_wall_x, raying.v_wall_y - raying.vrt))
		{
			//my_mlx_pixel_put(&map->m_mlx.img, raying.v_wall_x, raying.v_wall_y, 0x00ff00);
			break;
		}
		
		if (raying.vrt == 1)
			raying.v_step_y = -BSIZE;
		else if (raying.vrt == -1)
			raying.v_step_y = BSIZE;
		raying.v_wall_y += raying.v_step_y;
		
		raying.v_step_x = map->p_x - raying.vrt * (fabs(map->p_y - (raying.v_wall_y)) * tan(deg2rad(angle)));
		raying.v_step_x = raying.v_step_x - raying.v_wall_x;
		raying.v_wall_x += raying.v_step_x;
	}
	
	while(1 && raying.hor != 0)
	{
		printf("%d, angle = %f\n", raying.vrt, angle);
		if (is_wall(map, raying.h_wall_x - raying.hor, raying.h_wall_y))
		{
			//my_mlx_pixel_put(&map->m_mlx.img, raying.h_wall_x, raying.h_wall_y, 0xff0000);
			break;
		}
		if (raying.hor == 1)
			raying.h_step_x = -BSIZE;
		else if (raying.hor == -1)
			raying.h_step_x = BSIZE;
		raying.h_wall_x += raying.h_step_x;
		raying.h_step_y = map->p_y - raying.hor * (fabs(map->p_x - raying.h_wall_x) * tan(deg2rad(90 - angle)));
		raying.h_step_y = raying.h_step_y - raying.h_wall_y;
		raying.h_wall_y += raying.h_step_y;
	}
	// x = 0;
	dstwalldraw(map, &raying, raying.v_wall_x, raying.v_wall_y - raying.vrt, raying.h_wall_x - raying.hor, raying.h_wall_y, x);
}