/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:44:04 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 13:30:43 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	creatergb(int r, int g, int b)
{
	unsigned long	color;

	color = r << 16;
	color += g << 8;
	color += b;
	return ((int)color);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_block(int y, int x, t_elm_map	*map, int color)
{
	int	j;
	int	i;

	j = y * BSIZE;
	while (j < (y * BSIZE) + BSIZE)
	{
		i = x * BSIZE;
		while (i < (x * BSIZE) + BSIZE)
		{
			my_mlx_pixel_put(&map->m_mlx.img, i, j, color);
			i++;
		}
		j++;
	}
}

int	round_base(int nbr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((nbr + i) % PSIZE != 0)
		i++;
	while ((nbr - j) % PSIZE != 0)
		j++;
	if (i < j)
		return (nbr + i);
	else
		return (nbr - j);
}

void	draw_map_2d(t_elm_map	*map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y] && y < map->line_nbr)
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '1')
				put_block(y, x, map, 0x333333);
			else if (map->map[y][x] == '0')
				put_block(y, x, map, 0x777777);
			x++;
		}
		y++;
	}
}
