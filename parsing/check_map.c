/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:54:55 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 13:55:06 by oakoudad         ###   ########.fr       */
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
		put_error("Error\nDeplucate type\n");
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

void	check_digits(char	**rgb, t_elm_map *map, char *line)
{
	int	i;
	int	j;

	if (!rgb || ft_arrlen((void **)rgb) != 3)
	{
		free(line);
		close(map->texture_fd[0]);
		put_error("Error\nRGB format not valid\n");
	}
	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j] && ft_isdigit(rgb[i][j]))
			j++;
		if (rgb[i][j] != 0)
		{
			free(line);
			put_error("Error\nRGB format not valid\n");
		}
		i++;
	}
}

void	set_colors(char *line, t_color	*color, char **rgb)
{
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r > 255 || color->g > 255 || color->b > 255)
	{
		free(line);
		put_error("Error\nRGB format not valid\n");
	}
}

void	check_color(char *line, t_elm_map *map)
{
	char	*s;
	char	**rgb;
	t_color	*color;
	char	*newline;

	newline = ignore_space(line);
	if ((newline[0] == 'F' && map->floor.r != -1)
		|| (newline[0] == 'C' && map->ceiling.r != -1))
		put_error("Error\nDeplucate type\n");
	if (newline[0] == 'F')
		color = &map->floor;
	else
		color = &map->ceiling;
	s = get_informations(newline + 1);
	rgb = ft_split(s, ',');
	check_digits(rgb, map, line);
	set_colors(line, color, rgb);
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
	else if (ft_strstart(line, "1"))
		return ;
	else
		put_error("Error\nInvalid type\n");
}
