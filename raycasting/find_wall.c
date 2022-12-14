/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:52:39 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/17 16:48:53 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall_or_space(int x, int y, t_elm_map *map)
{
	if (map->map[y][x] == '1' || map->map[y][x] == ' ')
		return (1);
	return (0);
}

void	dst_draw(t_elm_map *map, t_raying *r, int x)
{
	float	distv;
	float	disth;
	t_txt	data;

	distv = -1;
	disth = -1;
	if (is_wall(map, r->v_wall_x, r->v_wall_y - r->vrt) == 1)
		distv = dist(map, r->v_wall_x, r->v_wall_y);
	if (is_wall(map, r->h_wall_x - r->hor, r->h_wall_y) == 1)
		disth = dist(map, r->h_wall_x, r->h_wall_y);
	if (distv != -1 && disth != -1)
	{
		if (distv < disth)
			data = init_data(r->v_wall_x, r->v_wall_y, fix_angle(r->angl), 'v');
		else
			data = init_data(r->h_wall_x, r->h_wall_y, fix_angle(r->angl), 'h');
		draw_wall(map, x, data, r);
		return ;
	}
	if (disth != -1)
	{
		data = init_data(r->h_wall_x, r->h_wall_y, fix_angle(r->angl), 'h');
		draw_wall(map, x, data, r);
	}
	dst_draw_norm(map, r, x, distv);
}

void	get_hor_wall(t_elm_map *map, t_raying	*raying, float angle)
{
	while (1 && raying->hor != 0)
	{
		if (is_wall(map, raying->h_wall_x - raying->hor, raying->h_wall_y))
			break ;
		if (raying->hor == 1)
			raying->h_step_x = -BSIZE;
		else if (raying->hor == -1)
			raying->h_step_x = BSIZE;
		raying->h_wall_x += raying->h_step_x;
		raying->h_step_y = map->p_y - raying->hor
			* (fabs(map->p_x - raying->h_wall_x) * tan(deg2rad(90 - angle)));
		raying->h_step_y = raying->h_step_y - raying->h_wall_y;
		raying->h_wall_y += raying->h_step_y;
	}
	if (raying->hor == 0)
	{
		raying->h_wall_x = -100000000;
		raying->h_wall_y = -100000000;
	}
}

void	get_vrt_wall(t_elm_map *map, t_raying	*raying, float angle)
{
	while (1 && raying->vrt != 0)
	{
		if (is_wall(map, raying->v_wall_x, raying->v_wall_y - raying->vrt))
			break ;
		if (raying->vrt == 1)
			raying->v_step_y = -BSIZE;
		else if (raying->vrt == -1)
			raying->v_step_y = BSIZE;
		raying->v_wall_y += raying->v_step_y;
		raying->v_step_x = map->p_x - raying->vrt
			* (fabs(map->p_y - (raying->v_wall_y)) * tan(deg2rad(angle)));
		raying->v_step_x = raying->v_step_x - raying->v_wall_x;
		raying->v_wall_x += raying->v_step_x;
	}
	if (raying->vrt == 0)
	{
		raying->v_wall_x = -100000000;
		raying->v_wall_y = -100000000;
	}
}

void	init_raying(t_elm_map *map, float *angle, t_raying	*raying)
{
	raying->vrt = 1;
	raying->hor = 1;
	raying->angl = *angle;
	*angle = fix_angle(map->dir + *angle);
	if ((*angle > 270 && *angle <= 360) || (*angle >= 0 && *angle < 90))
		raying->vrt = -1;
	else if (*angle == 270 || *angle == 90)
		raying->vrt = 0;
	if ((*angle > 0 && *angle < 180))
		raying->hor = -1;
	else if (*angle == 0 || *angle == 360 || *angle == 180)
		raying->hor = 0;
	raying->v_wall_y = floor(map->p_y / BSIZE) * BSIZE;
	if (raying->vrt == -1)
		raying->v_wall_y += BSIZE;
	raying->v_wall_x = map->p_x - raying->vrt
		* (fabs(map->p_y - raying->v_wall_y) * tan(deg2rad(*angle)));
	raying->h_wall_x = floor(map->p_x / BSIZE) * BSIZE;
	if (raying->hor == -1)
		raying->h_wall_x += BSIZE;
	raying->h_wall_y = map->p_y - raying->hor
		* (fabs(map->p_x - raying->h_wall_x) * tan(deg2rad(90 - *angle)));
}
