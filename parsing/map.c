/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:46:21 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 18:55:38 by oakoudad         ###   ########.fr       */
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
	map->map[i][j] = '\0';
	j = 0;
	while (line[j] && line[j] != '\n')
	{
		map->map[i][j] = line[j];
		j++;
	}
}

int	init_map(char *path, t_elm_map	*map)
{
	int		i;
	int		fd;
	char	*line;

	map->map = malloc(sizeof(char *) * map->line_nbr + 1);
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
			full_row(map, line, i);
			i++;
		}
		free(line);
	}
	map->map[i] = NULL;
	return (1);
}
