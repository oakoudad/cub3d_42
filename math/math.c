/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:57:37 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/12 00:32:09 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

float	distance(int xa, int ya, int xb, int yb)
{
	return (sqrt(pow(xb - xa, 2) + pow(yb - ya, 2)));
}

double	deg2rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	rad2deg(double rad)
{
	return (rad * (180 / M_PI));
}
