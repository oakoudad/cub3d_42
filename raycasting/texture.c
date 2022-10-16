/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:29:31 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 11:53:05 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_texture(t_elm_map *map, t_txt *txt)
{
	int		*txtcolor;
	float	yy;

	if (txt->c == 'v')
	{
		yy = txt->y * (map->texture_ea.width / txt->h);
		txtcolor = map->texture_ea.img.addr +((int)yy
				* (map->texture_ea.img.line_length / 4) + (int)txt->x);
	}
	else
	{
		yy = txt->y * (map->texture_no.width / txt->h);
		txtcolor = map->texture_no.img.addr + ((int)yy
				* (map->texture_no.img.line_length / 4) + (int)txt->x);
	}
	return (*txtcolor);
}
