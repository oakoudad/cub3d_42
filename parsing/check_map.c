/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:54:55 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 12:20:17 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_informations(char *line)
{
	int		len;
	char	*dup;

	while (line && *line != 0 && *line == ' ')
		line++;
	dup = ft_strdup(line);
	len = ft_strlen(dup) - 1;
	while (dup && (dup[len] == '\n' || dup[len] == ' '))
	{
		dup[len] = 0;
		len--;
	}
	return (dup);
}

void	check_files(char *line, t_elm_map *map, int index)
{
	int		i;
	char	*file;

	if (map->texture_fd[index] != -1)
	{
		printf("error {%s}\n", line);
		put_error("error\nDeplucate type\n");
	}
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	file = get_informations(&line[i + 2]);
	map->texture_fd[index] = open(file, O_RDONLY);
	i = 0;
	if (map->texture_fd[index] == -1)
	{
		write(2, "error: '", 9);
		write(2, file, ft_strlen(file) - 1);
		write(2, "'", 1);
		perror(" ");
		free(file);
		free(line);
		while (i < 4)
		{
			close(map->texture_fd[i]);
			i++;
		}
		exit(1);
	}
	free(file);
}

char	*ignore_space(char *haystack)
{
	while (haystack && ft_isspace(*haystack) && *haystack != '\n')
		haystack++;
	return (haystack);
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
	if (needle[i] == '\0')
		return (1);
	return (0);
}

void

void	check_color(char *line, t_elm_map *map)
{
	char	*rgb;
	t_color	*color;

	line = ignore_space(line);
	if ((line[0] == 'F' && map->floor.r != -1)
		|| (line[0] == 'C' && map->ceiling.r != -1))
		put_error("error\nDeplucate type\n");
	if (line[0] == 'F')
		color = &map->floor;
	else
		color = &map->ceiling;
	rgb = get_informations(line + 1);
	ft_split(rgb, ',');
	check_digits(rgb);
	color->b = 1;
	printf("%s\n", rgb);
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]) && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

void	check_map(char *line, t_elm_map *map)
{
	if (check_empty_line(line))
		return ;
	else if (ft_strstart(line, "NO "))
		check_files(line, map, NO);
	else if (ft_strstart(line, "SO "))
		check_files(line, map, SO);
	else if (ft_strstart(line, "WE "))
		check_files(line, map, WE);
	else if (ft_strstart(line, "EA "))
		check_files(line, map, EA);
	else if (ft_strstart(line, "F "))
		check_color(line, map);
	else if (ft_strstart(line, "C "))
		check_color(line, map);
	else
		return ;
}
