/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:22:13 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/21 12:39:08 by oakoudad         ###   ########.fr       */
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
	map->line_nbr = 0;
	map->longer_line = 0;
	map->player = 0;
}

int	main(int ac, char **av)
{
	t_elm_map	map;

	init_struct(&map);
	check_inputs(ac, av);
	read_file(av[1], &map);
	if (!init_map(av[1], &map))
		return (0);
	check_prepare_map(&map);
	printf("\nfile NO = %d => %s\n", map.texture_fd[NO], map.texture.no);
	printf("file SO = %d => %s\n", map.texture_fd[SO], map.texture.so);
	printf("file WE = %d => %s\n", map.texture_fd[WE], map.texture.we);
	printf("file EA = %d => %s\n", map.texture_fd[EA], map.texture.ea);
	printf("Color F RGB = %d, %d, %d\n", map.floor.r, map.floor.g, map.floor.b);
	printf("Color C RGB = %d, %d, %d\n",
		map.ceiling.r, map.ceiling.g, map.ceiling.b);
	printf("MAP line = %d\n", map.line_nbr);
	printf("MAP longer line = %d\n", map.longer_line);
	//while (1)
	//{
	//	(void)map;
	//}
}
