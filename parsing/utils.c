/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 00:19:17 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/17 17:49:15 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_array(t_elm_map *map, char *line, char *newline)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (newline[i])
	{
		if (newline[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		free(line);
		put_error("Error\nRGB format not valid\nExample : F 255, 255, 255\n", map);
	}
}

void	set_direction(t_elm_map *map, char c)
{
	if (c == 'N')
		map->dir = 180;
	if (c == 'E')
		map->dir = 270;
	if (c == 'S')
		map->dir = 0;
	if (c == 'W')
		map->dir = 90;
}
