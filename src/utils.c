/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:50:36 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/19 18:13:49 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	put_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

size_t	ft_strlen(const char	*s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	i = 0;
	while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}
