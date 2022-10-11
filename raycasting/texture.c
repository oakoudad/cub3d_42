/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:29:31 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/11 02:09:47 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int create_texture(char *addr,int whith,  int x, int y)
{
	unsigned int txtcolor;
	puts("create_texture");
	txtcolor =(unsigned int)(addr + (y * whith) + x);
	return(txtcolor);
}
