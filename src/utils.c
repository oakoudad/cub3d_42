/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:50:36 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/20 16:03:11 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	put_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

int	ft_arrlen(void **arr)
{
	int	i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*ignore_space(char *haystack)
{
	while (haystack && ft_isspace(*haystack) && *haystack != '\n')
		haystack++;
	return (haystack);
}
