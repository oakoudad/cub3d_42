/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:59:52 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/17 17:47:44 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_digits(char	**rgb, t_elm_map *map, char *line)
{
	int	i;
	int	j;

	if (!rgb || ft_arrlen((void **)rgb) != 3)
	{
		free(line);
		close(map->texture_fd[0]);
		put_error("Error\nRGB format not valid\n", map);
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
			put_error("Error\nRGB format not valid\n", map);
		}
		i++;
	}
}

void	set_colors(char *line, t_color	*color, char **rgb, t_elm_map *map)
{
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	if (color->r > 255 || color->g > 255 || color->b > 255)
	{
		free(line);
		put_error("Error\nRGB format not valid\n", map);
	}
}

char	*get_informations(char *line)
{
	int		len;
	char	*dup;

	while (line && *line != 0 && ft_isspace(*line))
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

void	check_color(char *line, t_elm_map *map)
{
	char	*s;
	char	**rgb;
	t_color	*color;
	char	*newline;

	newline = ignore_space(line);
	if ((newline[0] == 'F' && map->floor.r != -1)
		|| (newline[0] == 'C' && map->ceiling.r != -1))
		put_error("Error\nDeplucate type\n", map);
	if (newline[0] == 'F')
		color = &map->floor;
	else
		color = &map->ceiling;
	check_array(map, line, newline);
	s = get_informations(newline + 1);
	rgb = ft_split(s, ',');
	free(s);
	check_digits(rgb, map, line);
	set_colors(line, color, rgb, map);
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
