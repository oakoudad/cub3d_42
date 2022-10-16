/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:31:05 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/16 16:59:03 by eelmoham         ###   ########.fr       */
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
	map->keys.hor = 0;
	map->keys.vrt = 0;
	map->keys.cam = 0;
}

int	release(int key, t_elm_map	*map)
{
	puts("here");
	if (key == W || key == S)
		map->keys.vrt = 0;
	if (key == A || key == D)
		map->keys.hor = 0;
	if (key == CAMERA_L || key == CAMERA_L)
		map->keys.cam = 0;
	return (0);
}

int	key_press(int key, t_elm_map *map)
{
	if (key == W)
		map->keys.vrt = 1;
	else if (key == S)
		map->keys.vrt = -1;
	if (key == A)
		map->keys.hor = 1;
	else if (key == D)
		map->keys.hor = -1;
	if (key == CAMERA_R)
		map->keys.cam = 'R';
	if (key == CAMERA_L)
		map->keys.cam = 'L';
	events(key, map);
	return (0);
}

int	main(int ac, char **av)
{
	t_elm_map	map;
	int			fd;

	init_struct(&map);
	check_inputs(ac, av);
	read_file(av[1], &map);
	fd = open(av[1], O_RDONLY);
	if (!fd)
		return (0);
	if (!init_map(&map, fd))
		return (0);
	close(fd);
	check_map(&map);
	map.map = map.check_map + 1;
	raycasting_main(&map);
	mlx_hook(map.m_mlx.win3d, 2, (1L << 0), release, &map);
	mlx_hook(map.m_mlx.win3d, 2, (1L << 0), key_press, &map);
	//mlx_key_hook(map.m_mlx.win3d, events, &map);
	mlx_loop(map.m_mlx.mlx);
}
