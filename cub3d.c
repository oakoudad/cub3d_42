/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:22:13 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 12:13:40 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	init_struct(t_elm_map	*map)
{
	map->texture_fd[NO] = -1;
	map->texture_fd[SO] = -1;
	map->texture_fd[WE] = -1;
	map->texture_fd[EA] = -1;
	map->floor.r = -1;
	map->floor.g = -1;
	map->floor.b = -1;
	map->ceiling.r = -1;
	map->ceiling.g = -1;
	map->ceiling.b = -1;
}

int	main(int ac, char **av)
{
	t_elm_map	map;

	init_struct(&map);
	check_inputs(ac, av, &map);
	printf("file NO = %d\n", map.texture_fd[NO]);
	printf("file SO = %d\n", map.texture_fd[SO]);
	printf("file WE = %d\n", map.texture_fd[WE]);
	printf("file EA = %d\n", map.texture_fd[EA]);
	printf("file F RGB = %d, %d, %d\n", map.floor.r, map.floor.g, map.floor.b);
	printf("file C RGB = %d, %d, %d\n"
		, map.ceiling.r, map.ceiling.g, map.ceiling.b);
}
