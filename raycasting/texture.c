/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:29:31 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/14 00:13:03 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_texture(int x, float y, t_elm_map *map, float h)
{
	int		*txtcolor;
	int		yy;

	yy = y * (map->txtimg.width / h);
	//yy = 499;
	//printf("x = %f, y = %f\n", x, y);
	//printf("cx = %f, cy = %f\n", xx, yy);
	//printf("tH = %d, lH  = %f\n", map->txtimg.height, h);
	txtcolor = map->txtimg.img.addr + (yy * (map->txtimg.img.line_length  / 4) + x);
	return(*txtcolor);
}
