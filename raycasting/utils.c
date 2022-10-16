/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:37:09 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 15:16:23 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_txt	init_data(float x, float y, float h, char c)
{
	t_txt	data;

	data.x = x;
	data.y = y;
	data.h = h;
	data.c = c;
	return (data);
}

void	dst_draw_norm(t_elm_map *map, t_raying *r, int x, float distv)
{
	t_txt	data;

	data = init_data(r->v_wall_x, r->v_wall_y, fix_angle(r->angl), 'v');
	if (distv != -1)
		draw_wall(map, x, data, r);
}
