/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raying.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:49:48 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/06 00:27:11 by eelmoham         ###   ########.fr       */
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

int is_wall(t_elm_map *map, int x, int y)
{
	if (y / BSIZE >= 0  && y / BSIZE < map->line_nbr && x / BSIZE >= 0 && x / BSIZE <= map->longer_line && map->map[y/BSIZE][x/BSIZE] == '1')
		return (1);
	else if (y / BSIZE < 0 || x / BSIZE < 0 || x / BSIZE > map->longer_line || y / BSIZE > map->line_nbr)
		return (1);
	else
		return (-1);
}

int dstwalldraw(t_elm_map *map,t_raying *r, float angl,float xv, float yv, float xh, float yh)
{
	float distv;
	float disth;

	distv = -1;
	disth = -1;

	if ((is_wall(map, xv, yv) == 1) || (r->hor == 0 && is_wall(map, xv, yv) == 1))
		distv = dist(map, xv, yv);
	if ((is_wall(map, xh, yh) == 1) || (r->vrt == 0 && is_wall(map, xh, yh) == 1))
		disth = dist(map, xh, yh);

	// printf("dsith %f distv %f\n", disth, distv);
	// exit(1);
	if (disth != -1 && distv != -1)
	{
		if (disth < distv)
			return(rsaaam(map, xh, yh, angl, 0));
		else
			return(rsaaam(map, xv, yv, angl, 0));
	}
	else
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
	printf("****>> %f\n", angle);
	if ((angle > 270 && angle <= 360) || (angle >= 0 && angle < 90))
		raying.vrt  = -1;
	else if (angle == 270 || angle == 90)
		raying.vrt  = 0;
	if ((angle > 0 && angle < 180)){
		puts("111");
		raying.hor = -1;}
	else if (angle == 0 || angle == 360 || angle == 180)
		raying.hor  = 0;
	
	
	raying.v_wall_y = floor(map->p_y / BSIZE) * BSIZE;
	if (raying.vrt == -1)
		raying.v_wall_y += BSIZE;
	raying.v_wall_x = map->p_x + -raying.vrt * (fabs(map->p_y - raying.v_wall_y) * tan(deg2rad(angle)));
	
	// raying.h_wall_x = floor(map->p_x / BSIZE) * BSIZE;
	// if (raying.hor == -1)
	// 	raying.h_wall_x += BSIZE;
	// raying.h_wall_y = map->p_y + -raying.hor * (fabs(map->p_x - raying.h_wall_x) * tan(deg2rad(90 - angle)));
	

	// if (raying.v_wall_y / BSIZE >= 0  && raying.v_wall_y / BSIZE < map->line_nbr && raying.v_wall_x / BSIZE >= 0 && raying.v_wall_x / BSIZE <= map->longer_line)
	// 	my_mlx_pixel_put(&map->m_mlx.img, raying.v_wall_x, raying.v_wall_y, 0x00ff00);
	// if (raying.h_wall_y / BSIZE >= 0  && raying.h_wall_y / BSIZE < map->line_nbr && raying.h_wall_x / BSIZE >= 0 && raying.h_wall_x / BSIZE <= map->longer_line)
	// 	my_mlx_pixel_put(&map->m_mlx.img, raying.h_wall_x, raying.h_wall_y, 0xff0000);

	if (raying.vrt == 1)
		raying.v_wall_y -= BSIZE;
	else
		raying.v_wall_y += BSIZE;

	raying.v_wall_x = map->p_x + -raying.vrt * (fabs(map->p_y - raying.v_wall_y) * tan(deg2rad(angle)));
	
	if (raying.v_wall_y / BSIZE >= 0 && raying.v_wall_y / BSIZE < map->line_nbr && raying.v_wall_x / BSIZE >= 0 && raying.v_wall_x / BSIZE <= map->longer_line)
		my_mlx_pixel_put(&map->m_mlx.img, raying.v_wall_x, raying.v_wall_y, 0x0000ff);
	if (raying.vrt == 1)
		raying.v_wall_y -= BSIZE;
	else
		raying.v_wall_y += BSIZE;

	raying.v_wall_x = map->p_x + -raying.vrt * (fabs(map->p_y - raying.v_wall_y) * tan(deg2rad(angle)));
	
	if (raying.v_wall_y / BSIZE >= 0 && raying.v_wall_y / BSIZE < map->line_nbr && raying.v_wall_x / BSIZE >= 0 && raying.v_wall_x / BSIZE <= map->longer_line)
		my_mlx_pixel_put(&map->m_mlx.img, raying.v_wall_x, raying.v_wall_y, 0x0000ff);
	
	while (dstwalldraw(map, &raying, raying.angl, raying.v_wall_x, raying.v_wall_y, raying.h_wall_x, raying.h_wall_y) == -1)
	{
		
	}
	x = 0;
}

// float	find_wall(t_elm_map *map, float angle, float x)
// {
// 	// float	h_wall_x = 0;
// 	// float	h_wall_y = 0;
// 	// float	v_wall_x;
// 	// float	v_wall_y;
// 	// int		h = -1;
// 	// int		v = -1;
	
// 	// (void)x;
// 	// angle = correct_angle(map->dir + angle);
// 	// if ((angle >= 270 && angle <= 360) || (angle >= 0 && angle < 90))
// 	// 	v = 1;
// 	// if (!(angle > 180 && angle < 360))
// 	// 	h = 1;
// 	// v_wall_y = floor(map->p_y / BSIZE) * BSIZE;
// 	// if (v == 1)
// 	// 	v_wall_y += BSIZE;
// 	// v_wall_x = map->p_x + v * (fabs(map->p_y - v_wall_y) * tan(deg2rad(angle)));

// 	// h_wall_x = floor(map->p_x / BSIZE) * BSIZE;
// 	// if (h == 1)
// 	// 	h_wall_x += BSIZE;
// 	// h_wall_y = map->p_y + h * (fabs(map->p_x - h_wall_x) * tan(deg2rad(90 - angle)));
	
// 	// if (h_wall_y / BSIZE >= 0  && h_wall_y / BSIZE < map->line_nbr && h_wall_x / BSIZE >= 0 && h_wall_x / BSIZE <= map->longer_line)
// 	// 	my_mlx_pixel_put(&map->m_mlx.img, h_wall_x, h_wall_y, 0xff0000);// Red, X, hiresiontal
// 	// if (v_wall_y / BSIZE >= 0  && v_wall_y / BSIZE < map->line_nbr && v_wall_x / BSIZE >= 0 && v_wall_x / BSIZE <= map->longer_line)
// 	// 	my_mlx_pixel_put(&map->m_mlx.img, v_wall_x, v_wall_y, 0x00ff00);// green, Y, verticale
	
//  	return(-1);
// }

