/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:17:23 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/16 15:04:31 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_map(t_elm_map *map)
{
	int	j;

	j = 0;
	while (j <= 150)
	{
		draw_map2(map, j);
		j++;
	}
	player_point(map, 150, 150);
}

void	draw_3d(t_elm_map *map)
{
	float	end_x;
	float	end_y;
	float	i;
	float	j;

	i = 30;
	j = 0;
	while (i <= 30 && i >= -30)
	{
		end_x = sin(deg2rad(map->dir + i)) * 20 + map->p_x;
		end_y = cos(deg2rad(map->dir + i)) * 20 + map->p_y;
		findwall(map, i, j);
		i -= .03;
		j = j + 1;
	}
	draw_map(map);
	mlx_put_image_to_window(map->m_mlx.mlx, map->m_mlx.win3d,
		map->m_mlx.img3d.img, 0, 0);
}

void	init_texture(t_elm_map	*map)
{
	map->texture_no.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.no, &map->texture_no.width, &map->texture_no.height);
	map->texture_no.img.addr = (int *)mlx_get_data_addr(map->texture_no.img.img,
			&map->texture_no.img.bits_per_pixel,
			&map->texture_no.img.line_length, &map->texture_no.img.endian);
	map->texture_ea.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.ea,
			&map->texture_ea.width, &map->texture_ea.height);
	map->texture_ea.img.addr = (int *)mlx_get_data_addr(map->texture_ea.img.img,
			&map->texture_ea.img.bits_per_pixel,
			&map->texture_ea.img.line_length, &map->texture_ea.img.endian);
	map->texture_so.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.so,
			&map->texture_so.width, &map->texture_so.height);
	map->texture_so.img.addr = (int *)mlx_get_data_addr(map->texture_so.img.img,
			&map->texture_so.img.bits_per_pixel,
			&map->texture_so.img.line_length, &map->texture_so.img.endian);
	map->texture_we.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.we,
			&map->texture_we.width, &map->texture_we.height);
	map->texture_ea.img.addr = (int *)mlx_get_data_addr(map->texture_we.img.img,
			&map->texture_we.img.bits_per_pixel,
			&map->texture_we.img.line_length, &map->texture_we.img.endian);
}

void	raycasting_main(t_elm_map	*map)
{
	map->m_mlx.mlx = mlx_init();
	map->m_mlx.win3d = mlx_new_window(map->m_mlx.mlx,
			WSCREEN, HSCREEN, "CUB3D!");
	map->m_mlx.img3d.img = mlx_new_image (map->m_mlx.mlx,
			WSCREEN, HSCREEN);
	map->m_mlx.img3d.addr = mlx_get_data_addr (map->m_mlx.img3d.img,
			&map->m_mlx.img3d.bits_per_pixel, &map->m_mlx.img3d.line_length,
			&map->m_mlx.img3d.endian);
	map->texture_no.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.no, &map->texture_no.width, &map->texture_no.height);
	map->texture_no.img.addr = (int *)mlx_get_data_addr(map->texture_no.img.img,
			&map->texture_no.img.bits_per_pixel,
			&map->texture_no.img.line_length, &map->texture_no.img.endian);
	map->texture_ea.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.ea,
			&map->texture_ea.width, &map->texture_ea.height);
	map->texture_ea.img.addr = (int *)mlx_get_data_addr(map->texture_ea.img.img,
			&map->texture_ea.img.bits_per_pixel,
			&map->texture_ea.img.line_length, &map->texture_ea.img.endian);
	draw_3d(map);
}
