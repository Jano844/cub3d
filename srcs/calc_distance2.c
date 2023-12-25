/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/25 16:00:59 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	player_pos_x = 1.1;
float	player_pos_y = 1;

char map[7][7] =
{
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', 'P', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
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

float	calc_sx_sy(float m, char dir)
{
	if (dir == 'y')
	{
		if (m == 0)
			return(INT32_MAX);
		m = 1/m;
	}
	return (sqrt(1 + pow(m, 2)));
}

int	check_wall_hit(char dir, int step_x, int step_y)
{
	if (map[(int)(player_pos_y + step_y + (player_pos_y - (int)player_pos_y))]
		[(int)(player_pos_x + step_x + (player_pos_x - (int)player_pos_x))] == '1')
			return (1);
	return (0);
}

float	calc_distance(float m, float angle)
{
	float	dist_x;
	float	dist_y;

	float	stepcount_x = 0;
	float	stepcount_y = 0;

	float	step_dir_y;
	float	step_dir_x;

	if (angle >= 0 && angle <= 180)
		step_dir_y = -1;
	else
		step_dir_y = 1;
	if (angle >= 90 && angle <= 270)
		step_dir_x = -1;
	else
		step_dir_x = 1;


	dist_x =  calc_sx_sy(m, 'x');
	dist_y = calc_sx_sy(m, 'y');
	while(1)
	{
		while (dist_x >= dist_y)
		{
			if (check_wall_hit('y', stepcount_x, stepcount_y))
				return ((stepcount_y - step_dir_y) * calc_sx_sy(m , 'y'));
			stepcount_y += step_dir_y;
			dist_y += calc_sx_sy(m, 'y');
			if (check_wall_hit('y', stepcount_x, stepcount_y))
				return ((stepcount_y - step_dir_y)* calc_sx_sy(m , 'y'));
		}
		while (dist_y > dist_x)
		{
			if (check_wall_hit('x', stepcount_x, stepcount_y))
				return ((stepcount_x - step_dir_x) * calc_sx_sy(m, 'x'));
			stepcount_x += step_dir_x;
			dist_x += calc_sx_sy(m, 'x');
			if (check_wall_hit('x', stepcount_x, stepcount_y))
				return ((stepcount_x - step_dir_x)* calc_sx_sy(m, 'x'));
		}
	}
}

float	startdist(float m, float angle, float *playerx, float *playery)
{
	float distx;
	float disty;

	disty =  1 - (*playery - (int)*playery);
	distx = 1 - (*playerx - (int)*playerx);
	if (angle >= 0 && angle <= 180)
		disty = 1 - disty;
	if (angle >= 90 && angle <= 270)
		distx = 1 - distx;

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
		return (tempx);;
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

int	main(int argc, char **argv)
{
	float	angle = atof(argv[1]);
	float	dist;
	float	m;
	float	playerx = 1.5;
	float	playery = 2.5;

	m = fabs(get_slope(angle));
	// dist = fabs(calc_distance(m, angle));
	// printf("Distance: %f\n", fabs(dist));
	dist += fabs(startdist(m, angle, &playerx, &playery));
	printf("%f  %f\n", playerx, playery);
	printf("Distance: %f\n", fabs(dist));
}
