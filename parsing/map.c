/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:29:04 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/17 17:51:18 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	full_row(t_elm_map	*map, char *line, int y)
{
	int	x;

	map->check_map[y] = malloc(sizeof(char) * map->longer_line + 1);
	x = 0;
	while (x < map->longer_line)
	{
		map->check_map[y][x] = ' ';
		x++;
	}
	map->check_map[y][x] = '\0';
	x = 0;
	while (line[x] && line[x] != '\n')
	{
		map->check_map[y][x] = line[x];
		x++;
	}
}

void	check_space(t_elm_map *map, int y, int x)
{
	if (!(map->check_map[y][x + 1] == ' ' || map->check_map[y][x + 1] == '1'
		|| map->check_map[y][x + 1] == '\0'))
		put_error("Error: The wall is not closed\n", map);
	if (x > 0 && !(map->check_map[y][x - 1] == ' '
		|| map->check_map[y][x - 1] == '1'))
		put_error("Error: The wall is not closed\n", map);
	if (map->check_map[y + 1] && !(map->check_map[y + 1][x] == ' '
		|| map->check_map[y + 1][x] == '1'))
		put_error("Error: The wall is not closed\n", map);
	if (y > 0 && !(map->check_map[y - 1][x] == ' '
		|| map->check_map[y - 1][x] == '1'))
		put_error("Error: The wall is not closed\n", map);
}

void	map_char(t_elm_map *map, int y, int x)
{
	char	c;

	c = map->check_map[y][x];
	if (c == '0' || c == '1')
		return ;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->check_map[y][x] = '0';
		if (map->player > 0)
			put_error("Error: You can't enter more than one player\n", map);
		map->player++;
		map->p_x = (x * BSIZE) + (BSIZE) / 2;
		map->p_y = ((y - 1) * BSIZE) + (BSIZE) / 2;
		set_direction(map, c);
	}
	else if (c == ' ')
		check_space(map, y, x);
	else
		put_error("Error: Invalid map character\n", map);
}

int	check_map(t_elm_map	*map)
{
	int	x;
	int	y;

	y = 0;
	while (map->check_map[y])
	{
		x = 0;
		while (map->check_map[y][x])
		{
			map_char(map, y, x);
			x++;
		}
		y++;
	}
	return (1);
}

int	init_map(t_elm_map	*map, int fd)
{
	int		i;
	char	*line;
	int		is_map;

	is_map = 0;
	map->check_map = malloc(sizeof(char *) * (map->line_nbr + 3));
	i = 0;
	full_row(map, "", i++);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strstart(line, "1", map))
		{
			if (is_map == -1)
				put_error("Error: Empty line inside the map\n", map);
			is_map = 1;
			full_row(map, line, i++);
		}
		if (is_map == 1 && check_empty_line(line))
			is_map = -1;
		free(line);
	}
	return (full_row(map, "", i), map->check_map[i + 1] = NULL, 1);
}
