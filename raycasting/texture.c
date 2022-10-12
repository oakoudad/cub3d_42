/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:29:31 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/12 01:21:49 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int create_texture(int x, int y, t_elm_map *map, float h)
{
	char	*txtcolor;
	// int x_offset = 0;
	// int y_offset = 0;

(void)h;
	// (void)y_offset;
	// x_offset = ((float)x / h) * map->txtimg.height;
	// y_offset = y % map->txtimg.width;
	// // printf("x = %d, y = %d, width = %d\n", x_offset, y_offset, map->txtimg.width);
	txtcolor = (map->txtimg.img.addr + (y * map->txtimg.img.line_length + x * (map->txtimg.img.bits_per_pixel / 8)));
	// printf("txtcolor = %u\n", *((unsigned int *)txtcolor));
	return(*((unsigned int *)txtcolor));
}
