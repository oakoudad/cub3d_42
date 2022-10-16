/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:49:48 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 11:04:26 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	findwall(t_elm_map *map, float angle, float x)
{
	t_raying	raying;

	init_raying(map, &angle, &raying);
	get_vrt_wall(map, &raying, angle);
	get_hor_wall(map, &raying, angle);
	dst_draw(map, &raying, x);
}
