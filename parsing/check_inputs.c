/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:23:36 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 18:23:58 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_extension(char *haystack, char *needle)
{
	int	len_s;
	int	len_n;

	len_s = ft_strlen(haystack);
	len_n = ft_strlen(needle);
	if (len_s < len_n || ft_strcmp(&haystack[len_s - len_n], ".cub") != 0)
		put_error("Error\nPath map file should be like : exemple.cub\n");
}

void	read_file(char *path, t_elm_map *map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror("Error\n");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		check_map(line, map);
		free(line);
	}
	close(fd);
}

void	check_inputs(int ac, char **av)
{
	if (ac != 2)
		put_error("Error\nusage: ./cub3d [exemple.cub]\n");
	check_extension(av[1], ".cub");
}
