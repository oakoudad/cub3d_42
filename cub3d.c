/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:22:13 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 18:38:55 by oakoudad         ###   ########.fr       */
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
}

int	init_map(char *path, t_elm_map	*map)
{
	int		i;
	int		j;
	int		fd;
	char	*line;

	map->map = malloc(sizeof(char *) * map->line_nbr + 1);
	if (!map->map)
		return (0);
	fd = open(path, O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strstart(line, "1"))
		{
			map->map[i] = malloc(sizeof(char *) * map->longer_line + 1);
			j = 0;
			while (j < map->longer_line)
			{
				map->map[i][j] = ' ';
				j++;
			}
			map->map[i][j] = '\0';
			j = 0;
			while (line[j] && line[j] != '\n')
			{
				map->map[i][j] = line[j];
				j++;
			}
			i++;
		}
		free(line);
	}
	map->map[i] = NULL;
	i = 0;
	j = 0;
	while (j++ <= map->longer_line + 1)
		printf("_");
	while (map->map[i])
	{
		printf("{%s}\n", map->map[i]);
		i++;
	}
	j = 0;
	while (j++ <= map->longer_line + 1)
		printf("_");
	return (1);
}

int	main(int ac, char **av)
{
	t_elm_map	map;

	init_struct(&map);
	check_inputs(ac, av);
	read_file(av[1], &map);
	if (!init_map(av[1], &map))
		return (0);
	printf("\nfile NO = %d => %s\n", map.texture_fd[NO], map.texture.no);
	printf("file SO = %d => %s\n", map.texture_fd[SO], map.texture.so);
	printf("file WE = %d => %s\n", map.texture_fd[WE], map.texture.we);
	printf("file EA = %d => %s\n", map.texture_fd[EA], map.texture.ea);
	printf("Color F RGB = %d, %d, %d\n", map.floor.r, map.floor.g, map.floor.b);
	printf("Color C RGB = %d, %d, %d\n"
		, map.ceiling.r, map.ceiling.g, map.ceiling.b);
	printf("MAP line = %d\n", map.line_nbr);
	printf("MAP longer line = %d\n", map.longer_line);
	while (1);
}
