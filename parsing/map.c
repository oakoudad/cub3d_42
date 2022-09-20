/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:46:21 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 20:05:52 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	full_row(t_elm_map	*map, char *line, int i)
{
	int	j;

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
			put_error("Error: Wall not valid\n");
		if (x > 0 && !(map->map[y][x - 1] == ' ' || map->map[y][x - 1] == '1'))
			put_error("Error: Wall not valid\n");
		if (map->map[y + 1] && !(map->map[y + 1][x] == ' '
			|| map->map[y + 1][x] == '1'))
			put_error("Error: Wall not valid\n");
		if (y > 0 && !(map->map[y - 1][x] == ' '
			|| map->map[y - 1][x] == '1'))
			put_error("Error: Wall not valid\n");
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

	map->map = malloc(sizeof(char *) * map->line_nbr + 3);
	fd = open(path, O_RDONLY);
	map->map[0] = malloc(sizeof(char) * map->longer_line + 10);
	full_row(map, " ", 0);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strstart(line, "1"))
		{
			map->map[i] = malloc(sizeof(char) * map->longer_line + 10);
			full_row(map, line, i);
			i++;
		}
		free(line);
	}
	map->map[i] = malloc(sizeof(char *) * map->longer_line + 10);
	full_row(map, " ", i);
	map->map[i + 1] = NULL;
	return (1);
}
