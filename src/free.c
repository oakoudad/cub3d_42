/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:42:33 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/17 16:49:24 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	my_free(t_elm_map *map)
{
	if (map->texture.ea)
		ft_free(map->texture.ea);
	map->texture.ea = NULL;
	if (map->texture.no)
		ft_free(map->texture.no);
	map->texture.no = NULL;
	if (map->texture.so)
		ft_free(map->texture.so);
	map->texture.so = NULL;
	if (map->texture.we)
		ft_free(map->texture.we);
	map->texture.we = NULL;
}

int	close_game(t_elm_map *map)
{
	my_free(map);
	write(1, "Game closed successfully\n", 25);
	exit(0);
	return (0);
}

void	error_and_free(t_elm_map *map, char *message)
{
	(void)map;
	write(2, message, ft_strlen(message));
	exit(1);
}
