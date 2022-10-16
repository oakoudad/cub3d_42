/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:44:04 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 17:02:14 by eelmoham         ###   ########.fr       */
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
