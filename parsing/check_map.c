/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:54:55 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/19 19:11:48 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_file_path(char *line)
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

void	our_open(char *line, t_elm_map *map, int index)
{
	int		i;
	char	*file;

	if (map->texture_fd[index] != -1)
		put_error("error\nDeplucate type\n");
	file = get_file_path(line + 2);
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
		while (1);
	}
	free(file);
}

int	ft_strstart(char *haystack, char *needle)
{
	int	i;

	if (!haystack || !needle)
		return (0);
	i = 0;
	while (haystack[i] && needle[i] && haystack[i] == needle[i])
		i++;
	if (needle[i] == '\0')
		return (1);
	return (0);
}

void	check_map(char *line, t_elm_map *map)
{
	if (ft_strstart(line, "NO "))
		our_open(line, map, NO);
	if (ft_strstart(line, "SO "))
		our_open(line, map, SO);
	if (ft_strstart(line, "WE "))
		our_open(line, map, WE);
	if (ft_strstart(line, "EA "))
		our_open(line, map, EA);
}
