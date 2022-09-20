/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:54:55 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 18:58:27 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_files(char *line, t_elm_map *map, int index, char **f)
{
	int		i;
	char	*file;

	if (map->texture_fd[index] != -1)
		put_error("Error\nDeplucate type\n");
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	file = get_informations(&line[i + 2]);
	map->texture_fd[index] = open(file, O_RDONLY);
	if (map->texture_fd[index] == -1)
	{
		write(2, "error: '", 9);
		write(2, file, ft_strlen(file));
		write(2, "'", 1);
		perror(" ");
		free(file);
		free(line);
		exit(1);
	}
	close(map->texture_fd[index]);
	*f = ft_strdup(file);
	free(file);
}

int	ft_strstart(char *haystack, char *needle)
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
		put_error("Error\nTexture error\n");
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
		put_error("Error\nIncomplete number of elements\n");
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
	else if (ft_strstart(line, "NO"))
		check_files(line, map, NO, &(map->texture.no));
	else if (ft_strstart(line, "SO"))
		check_files(line, map, SO, &(map->texture.so));
	else if (ft_strstart(line, "WE"))
		check_files(line, map, WE, &(map->texture.we));
	else if (ft_strstart(line, "EA"))
		check_files(line, map, EA, &(map->texture.ea));
	else if (ft_strstart(line, "F"))
		check_color(line, map);
	else if (ft_strstart(line, "C"))
		check_color(line, map);
	else if (ft_strstart(line, "1"))
		count_map(line, map);
	else
		put_error("Error\nInvalid type\n");
}
