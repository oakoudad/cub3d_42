/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:52:46 by eelmoham          #+#    #+#             */
/*   Updated: 2022/09/20 13:12:53 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

//importaant function not exist in math c library;

float distance(int xa, int ya, int xb, int yb)
{
	return (sqrt(pow(xb - xa, 2) + pow(yb - ya, 2)));
}

double deg2rad(double deg)
{
	return (deg * (3.14 / 180));
}

double rad2deg(double rad)
{
	return (rad * (180/3.14));
}

// int main()
// {
// 	printf("%f\n", distance(1,1,4,2));
// 	printf("%f\n", deg2rad(30));
// 	printf("%f\n", rad2deg(1));
	
// 	return 0;
// }
