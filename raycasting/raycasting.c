/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:17:23 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/16 16:47:54 by eelmoham         ###   ########.fr       */
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
	mlx_clear_window(map->m_mlx.mlx, map->m_mlx.win3d);
	mlx_put_image_to_window(map->m_mlx.mlx, map->m_mlx.win3d,
		map->m_mlx.img3d.img, 0, 0);
}

void	check_xpm(t_elm_map	*map)
{
	if (map->txt_no.img.img == NULL)
		exit(0);
	if (map->txt_so.img.img == NULL)
		exit(0);
	if (map->txt_ea.img.img == NULL)
		exit(0);
	if (map->txt_we.img.img == NULL)
		exit(0);
}

void	init_texture(t_elm_map	*map)
{
	map->txt_no.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.no, &map->txt_no.width, &map->txt_no.height);
	map->txt_ea.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx, map->texture.ea,
			&map->txt_ea.width, &map->txt_ea.height);
	map->txt_so.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.so, &map->txt_so.width, &map->txt_so.height);
	map->txt_we.img.img = mlx_xpm_file_to_image(map->m_mlx.mlx,
			map->texture.we, &map->txt_we.width, &map->txt_we.height);
	check_xpm(map);
	map->txt_no.img.addr = (int *)mlx_get_data_addr(map->txt_no.img.img,
			&map->txt_no.img.bits_per_pixel,
			&map->txt_no.img.line_length, &map->txt_no.img.endian);
	map->txt_ea.img.addr = (int *)mlx_get_data_addr(map->txt_ea.img.img,
			&map->txt_ea.img.bits_per_pixel,
			&map->txt_ea.img.line_length, &map->txt_ea.img.endian);
	map->txt_so.img.addr = (int *)mlx_get_data_addr(map->txt_so.img.img,
			&map->txt_so.img.bits_per_pixel,
			&map->txt_so.img.line_length, &map->txt_so.img.endian);
	map->txt_we.img.addr = (int *)mlx_get_data_addr(map->txt_we.img.img,
			&map->txt_we.img.bits_per_pixel,
			&map->txt_we.img.line_length, &map->txt_we.img.endian);
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
	init_texture(map);
	draw_3d(map);
}
