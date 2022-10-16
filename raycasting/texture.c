/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:29:31 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/16 16:13:14 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_texture(t_elm_map *map, t_txt *txt, t_raying *r, t_txt *data)
{
	int				*txtcolor;
	float			y;
	t_textureimg	*txting;

	if (data->c == 'v')
	{
		if (r->vrt == -1)
			txting = &map->txt_so;
		else
			txting = &map->txt_no;
	}
	else
	{
		if (r->hor == -1)
			txting = &map->txt_ea;
		else
			txting = &map->txt_we;
	}
	y = txt->y * ((*txting).width / txt->h);
	txtcolor = (*txting).img.addr +((int)y * ((*txting).img.line_length / 4) + (int)txt->x);
	return (*txtcolor);
}
