/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:54:55 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/17 15:54:09 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_print(char *file)
{
	write(2, "error: '", 9);
	write(2, file, ft_strlen(file));
	write(2, "'", 1);
}

void	check_files(char *line, t_elm_map *map, int index, char **f)
{
	int		i;
	char	*file;

	if (map->texture_fd[index] != -1)
	{
		free(line);
		put_error("Error\nDeplucate type\n", map);
	}
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	file = get_informations(&line[i + 2]);
	map->texture_fd[index] = open(file, O_RDONLY);
	if (map->texture_fd[index] == -1)
	{
		error_print(file);
		perror(" ");
		free(file);
		free(line);
		my_free(map);
		exit(1);
	}
	close(map->texture_fd[index]);
	*f = ft_strdup(file);
	free(file);
}

int	ft_strstart(char *haystack, char *needle, t_elm_map *map)
{
	int	i;

	if (!haystack || !needle)
		return (0);
	haystack = ignore_space(haystack);
	i = 0;
	while (haystack[i] && needle[i] && haystack[i] == needle[i])
		i++;
	if (needle[i] == '\0' && haystack[i] != ' '
		&& haystack[i] != '\t' && haystack[0] != '1')
		put_error("Error\nMap wrong format\n", map);
	if (needle[i] == '\0')
		return (1);
	return (0);
}

void	count_map(char *line, t_elm_map *map)
{
	t_color	*c;
	t_color	*f;
	int		len;

	c = &map->ceiling;
	f = &map->floor;
	if (map->texture_fd[NO] == -1 || map->texture_fd[SO] == -1
		|| map->texture_fd[WE] == -1 || map->texture_fd[EA] == -1
		|| f->r == -1 || f->g == -1 || f->b == -1
		|| c->r == -1 || c->g == -1 || c->b == -1)
	{
		free(line);
		put_error("Error\nIncomplete number of elements\n", map);
	}
	map->line_nbr = map->line_nbr + 1;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len > map->longer_line)
		map->longer_line = len;
}

void	check_map_format(char *line, t_elm_map *map)
{
	if (check_empty_line(line))
		return ;
	else if (ft_strstart(line, "NO", map))
		check_files(line, map, NO, &(map->texture.no));
	else if (ft_strstart(line, "SO", map))
		check_files(line, map, SO, &(map->texture.so));
	else if (ft_strstart(line, "WE", map))
		check_files(line, map, WE, &(map->texture.we));
	else if (ft_strstart(line, "EA", map))
		check_files(line, map, EA, &(map->texture.ea));
	else if (ft_strstart(line, "F", map))
		check_color(line, map);
	else if (ft_strstart(line, "C", map))
		check_color(line, map);
	else if (ft_strstart(line, "1", map))
		count_map(line, map);
	else
	{
		free(line);
		put_error("Error\nInvalid type\n", map);
	}
}
