/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:29:31 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/17 18:46:16 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_texture(t_elm_map *map, t_txt *txt, t_raying *r, t_txt *data)
{
	int				*txtcolor;
	float			y;
	t_textureimg	txting;

	if (data->c == 'v')
	{
		if (r->vrt == -1)
			txting = map->txt_so;
		else
			txting = map->txt_no;
	}
	else
	{
		if (r->hor == -1)
			txting = map->txt_ea;
		else
			txting = map->txt_we;
	}
	y = txt->y * (txting.height / txt->h);
	printf("%d\n", (int)y * (txting.img.line_length / 4));
	txtcolor = txting.img.addr + ((int)y
			* (txting.img.line_length / 4) + (int)txt->x);
	return (*txtcolor);
}
