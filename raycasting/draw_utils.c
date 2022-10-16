/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 00:36:54 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/16 10:36:53 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	to_positive_angle(float angle)
{
	angle = fmodf(angle, 360);
	while (angle < 0)
		angle += 360.0;
	return (angle);
}

float	dist(t_elm_map *map, float endX, float endY)
{
	float	dst;

	dst = hypot(endX - map->p_x, endY - map->p_y);
	return (dst);
}

int	is_wall(t_elm_map *map, float x, float y)
{
	if ((int)(y / BSIZE) < 0 || (int)(y / BSIZE) >= map->line_nbr)
		return (-1);
	if ((int)(x / BSIZE) < 0 || (int)(x / BSIZE) >= map->longer_line)
		return (-1);
	if (map->map[(int)(y / BSIZE)][(int)(x / BSIZE)] == '0')
		return (0);
	return (1);
}
