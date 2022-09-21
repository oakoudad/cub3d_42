/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:46:21 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/21 13:50:13 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	full_row(t_elm_map	*map, char *line, int i)
{
	int	j;

	map->map[i] = malloc(sizeof(char) * map->longer_line + 10);
	j = 0;
	while (j < map->longer_line)
	{
		map->map[i][j] = ' ';
		j++;
	}
	map->map[i][map->longer_line] = '\0';
	j = 0;
	while (line[j] && line[j] != '\n')
	{
		map->map[i][j] = line[j];
		j++;
	}
}

void	map_char(t_elm_map *map, int y, int x)
{
	char	c;

	c = map->map[y][x];
	if (c == '0' || c == '1')
		return ;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (map->player > 0)
			put_error("Error: You can't enter more than one player\n");
		map->player++;
		map->p_x = x;
		map->p_y = y;
	}
	else if (c == ' ')
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
	int		status;

	status = 0;
	map->map = malloc(sizeof(char *) * map->line_nbr + 3);
	fd = open(path, O_RDONLY);
	full_row(map, " ", 0);
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strstart(line, "1"))
		{
			status = 1;
			full_row(map, line, i++);
		}
		if (status == 1 && check_empty_line(line))
			put_error("Error: Empty line inside the map\n");
		free(line);
	}
	full_row(map, " ", i);
	map->map[i + 1] = NULL;
	return (1);
}
