/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/27 14:07:04 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define WIDTH 7
#define HEIGHT 7

char map[HEIGHT][WIDTH] =
{
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', 'P', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '1'},
		{'1', '1', '1', '1', '1', '1', '1'}
};

float	get_slope(float angle)
{
	float	radianAngle;
	float	dirx;
	float	diry;

	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle == 90)
		return (INT32_MAX);
	if (angle == 270)
		return (INT32_MIN);
	radianAngle = (angle) * PI / 180.0;
	dirx = cos(radianAngle);
	diry = sin(radianAngle);
	return (diry/dirx);
}

float	startdist(float m, float angle, float *playerx, float *playery)
{
	float distx;
	float disty;

	disty =  1 - (*playery - (int)*playery);
	distx = 1 - (*playerx - (int)*playerx);
	if (angle >= 0 && angle <= 180)
		disty = 1 - disty;
	if (disty == 0 )
		disty = 1;
	if (angle >= 90 && angle <= 270)
		distx = 1 - distx;
	if (distx == 0 )
		distx = 1;

	distx *= 10;
	disty *= 10;

	if (angle == 0 || angle == 180)
	{
		if (angle >= 90 && angle <= 270)
			*playerx -= distx / 10;
		else
			*playerx += distx / 10;
		return (distx / 10);
	}
	if (angle == 90 || angle == 270)
	{
		if (angle >= 0 && angle <= 180)
			*playery -= disty / 10;
		else
			*playery += disty / 10;
		return (disty / 10);
	}
	float tempx = (distx * sqrt(1 + pow(m, 2))) / 10;
	float tempy = (disty * sqrt(1 + pow(1/m, 2))) / 10;
	if (m == 0)
		return (tempx);
	if (tempx < tempy)
	{
		if (angle >= 90 && angle <= 270)
			*playerx -= distx / 10;
		else
			*playerx += distx / 10;

		if (angle >= 0 && angle <= 180)
			*playery -= sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		else
			*playery += sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		return (tempx);
	}
	if (angle >= 0 && angle <= 180)
		*playery -= disty / 10;
	else
		*playery += disty / 10;

	if (angle >= 90 && angle <= 270)
		*playerx -= sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	else
		*playerx += sqrt(pow(tempy, 2) - pow((disty / 10), 2));

	return (tempy);
}

float	get_phi(float gegen, float an)
{
	float	rad_angle;
	float	deg_angle;

	rad_angle = atan2(gegen, an);
	deg_angle = (rad_angle * 180) / PI;
	if (deg_angle < 0)
		deg_angle = 360 + deg_angle;
	return(deg_angle);
}

float	calc_distance(float angle, float playerx, float playery)
{
	float	dist = 0;
	float phi1 = get_phi(playery - 1, WIDTH - (playerx + 1));
	float phi2 = get_phi(-(HEIGHT - (playery + 1)), -(playerx - 1));
	int i = -1;
	int	tempy = playery;
	int	tempx = playerx;
	float last_dist = dist;
	float	m;

	m = fabs(get_slope(angle));
	while (map[tempy][tempx] != '1')
	{
		last_dist = dist;
		if (map[tempy][tempx] == '1')
			break ;
		dist += fabs(startdist(m, angle, &playerx, &playery));
		tempy = playery;
		tempx = playerx;
		if (map[tempy][tempx] == '1')
			break ;
	}
	if (angle > phi1 && angle < phi2)
		dist = last_dist;
	return (fabs(dist));
}

int	main(int argc, char **argv)
{
	float	angle = atof(argv[1]);
	float	playerx = 2;
	float	playery = 2;
	while (angle >= 360)
		angle -= 360;
	printf("%f\n", calc_distance(angle, playerx, playery));
}
