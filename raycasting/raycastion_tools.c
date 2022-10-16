/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastion_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:23:20 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 13:32:19 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_draw_wall(t_elm_map *map, t_txt data, t_drwall	*drwall)
{
	drwall->delta_x = data.x - map->p_x;
	drwall->delta_y = data.y - map->p_y;
	drwall->distance = sqrt((drwall->delta_x * drwall->delta_x)
			+ (drwall->delta_y * drwall->delta_y));
	drwall->distance = cos(deg2rad(data.h)) * fabs(drwall->distance);
	drwall->h = HSCREEN * BSIZE / (drwall->distance);
	drwall->yy = 0;
	drwall->to = (HSCREEN - drwall->h) / 2;
}

void	draw_wall(t_elm_map *map, float i, t_txt data)
{
	t_drwall	drwall;
	float		x;

	init_draw_wall(map, data, &drwall);
	while (drwall.yy >= 0 && drwall.yy < drwall.to && drwall.yy < HSCREEN)
		my_mlx_pixel_put(&map->m_mlx.img3d, (i), (drwall.yy++),
			creatergb(map->ceiling.r, map->ceiling.g, map->ceiling.b));
	while (drwall.yy >= drwall.to
		&& drwall.yy < drwall.to + drwall.h && drwall.yy < HSCREEN)
	{
		x = ((int)data.y % BSIZE) * map->texture_no.height / BSIZE;
		if (data.c == 'v')
			x = ((int)data.x % BSIZE) * map->texture_ea.height / BSIZE;
		drwall.txt.x = x;
		drwall.txt.y = drwall.yy - drwall.to;
		drwall.txt.c = data.c;
		drwall.txt.h = drwall.h;
		drwall.xcolor = create_texture(map, &drwall.txt);
		my_mlx_pixel_put(&map->m_mlx.img3d, i, drwall.yy++, drwall.xcolor);
	}
	while (drwall.yy < HSCREEN)
		my_mlx_pixel_put(&map->m_mlx.img3d, (i), (drwall.yy++),
			creatergb(map->floor.r, map->floor.g, map->floor.b));
}

int	draw_line(t_elm_map *map, float endX, float endY)
{
	float	delta_x;
	float	delta_y;
	int		pixels;

	delta_x = endX - (75 + 20);
	delta_y = endY - (75 + 20);
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	endX = (75 + 20);
	endY = (75 + 20);
	while (pixels && endY / BSIZE >= 0 && endX / BSIZE >= 0
		&& endX / BSIZE <= map->longer_line && endY / BSIZE <= map->line_nbr)
	{
		my_mlx_pixel_put(&map->m_mlx.img3d, endX, endY, 0x00ff00);
		endX += delta_x;
		endY += delta_y;
		--pixels;
	}
	return (1);
}

void	player_point(t_elm_map *map, int i, int j)
{
	draw_line(map, sin(deg2rad(map->dir))
		* 15 + 95, cos(deg2rad(map->dir)) * 15 + 95);
	my_mlx_pixel_put(&map->m_mlx.img3d, i / 2 + 20 + 1, j / 2 + 20, 0x001100);
	my_mlx_pixel_put(&map->m_mlx.img3d, i / 2 + 20 - 1, j / 2 + 20, 0x001100);
	my_mlx_pixel_put(&map->m_mlx.img3d, i / 2 + 20, j / 2 + 20, 0x001100);
	my_mlx_pixel_put(&map->m_mlx.img3d, i / 2 + 20, j / 2 + 20 + 1, 0x001100);
	my_mlx_pixel_put(&map->m_mlx.img3d, i / 2 + 20, j / 2 + 20 - 1, 0x001100);
}

void	draw_map2(t_elm_map *map, int j)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i <= 150)
	{
		y = map->p_y * MAPSIZE / BSIZE;
		y = y + (j - 75);
		x = map->p_x * MAPSIZE / BSIZE;
		x = x + (i - 75);
		if (y < 0 || (y / MAPSIZE) >= map->line_nbr
			|| x < 0 || (x / MAPSIZE) >= map->longer_line)
			my_mlx_pixel_put(&map->m_mlx.img3d, i + 20, j + 20, 0x333333);
		else if (map->map[(y / MAPSIZE)][(x / MAPSIZE)] == '0')
			my_mlx_pixel_put(&map->m_mlx.img3d, i + 20, j + 20, 0xcccccc);
		else
			my_mlx_pixel_put(&map->m_mlx.img3d, i + 20, j + 20, 0xaaaaaa);
		i++;
	}
}
