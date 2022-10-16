/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:29:31 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 09:55:53 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_texture(float x, float y, t_elm_map *map, float h, char c)
{
	int		*txtcolor;
	float	yy;

	if (c == 'v')
	{
		yy = y * (map->texture_ea.width / h);
		txtcolor = map->texture_ea.img.addr + ((int)yy * (map->texture_ea.img.line_length / 4) + (int)x);
	}
	else
	{
		yy = y * (map->texture_no.width / h);
		txtcolor = map->texture_no.img.addr + ((int)yy * (map->texture_no.img.line_length / 4) + (int)x);
	}
	return(*txtcolor);
}
