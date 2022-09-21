/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:04 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/21 22:55:59 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	full_row(t_elm_map	*map, char *line, int y)
{
	int	x;

	map->map[y] = malloc(sizeof(char) * map->longer_line + 1);
	x = 0;
	while (x < map->longer_line)
	{
		map->map[y][x] = ' ';
		x++;
	}
	map->map[y][x] = '\0';
	x = 0;
	while (line[x] && line[x] != '\n')
	{
		map->map[y][x] = line[x];
		x++;
	}
}

void	check_space(t_elm_map *map, int y, int x)
{
	if (!(map->map[y][x + 1] == ' ' || map->map[y][x + 1] == '1'
		|| map->map[y][x + 1] == '\0'))
		put_error("Error: The wall is not closed\n");
	if (x > 0 && !(map->map[y][x - 1] == ' ' || map->map[y][x - 1] == '1'))
		put_error("Error: The wall is not closed\n");
	if (map->map[y + 1] && !(map->map[y + 1][x] == ' '
		|| map->map[y + 1][x] == '1'))
		put_error("Error: The wall is not closed\n");
	if (y > 0 && !(map->map[y - 1][x] == ' '
		|| map->map[y - 1][x] == '1'))
		put_error("Error: The wall is not closed\n");
}

void	set_direction(t_elm_map *map, char c)
{
	if (c == 'N')
		map->dir = 180;
	if (c == 'E')
		map->dir = 270;
	if (c == 'S')
		map->dir = 0;
	if (c == 'W')
		map->dir = 90;
}

void	map_char(t_elm_map *map, int y, int x)
{
	char	c;

	c = map->map[y][x];
	if (c == '0' || c == '1')
		return ;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->map[y][x] = '0';
		if (map->player > 0)
			put_error("Error: You can't enter more than one player\n");
		map->player++;
		map->p_x = (x * BSIZE) + (BSIZE - PSIZE) / 2;
		map->p_y = ((y - 1) * BSIZE) + (BSIZE - PSIZE) / 2;
		set_direction(map, c);
	}
	else if (c == ' ')
		check_space(map, y, x);
	else
		put_error("Error: Invalid map character\n");
}

int	check_map(t_elm_map	*map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			map_char(map, y, x);
			x++;
		}
		y++;
	}
	return (1);
}

int	init_map(char *path, t_elm_map	*map)
{
	int		i;
	int		fd;
	char	*line;
	int		is_map;

	is_map = 0;
	map->map = malloc(sizeof(char *) * (map->line_nbr + 3));
	fd = open(path, O_RDONLY);
	i = 0;
	full_row(map, "", i++);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strstart(line, "1"))
		{
			is_map = 1;
			full_row(map, line, i++);
		}
		if (is_map == 1 && check_empty_line(line))
			put_error("Error: Empty line inside the map\n");
		free(line);
	}
	full_row(map, "", i);
	map->map[i + 1] = NULL;
	return (1);
}
