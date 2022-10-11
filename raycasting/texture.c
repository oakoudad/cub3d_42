/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:29:31 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/11 01:17:37 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int create_texture(t_elm_map *map, char *path, float x, float y)
{
	unsigned int txtcolor;
	
	map->txtimg.img =  mlx_xpm_file_to_image(&map->m_mlx.img, path, &map->txtimg.whith, &map->txtimg.height);
	map->txtimg.addr = mlx_get_data_addr(map->txtimg.img, &map->txtimg.bits_per_pixel, &map->txtimg.line_length, &map->txtimg.endian);
	
	txtcolor = (map->p_y * map->txtimg.whith) + map->p_x;
	return(txtcolor);
}
