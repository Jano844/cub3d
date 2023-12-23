/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/23 14:41:16 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	player_pos_x = 3;
int	player_pos_y = 3;

char map[7][7] =
{
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '1', '1'},
		{'1', '1', '1', 'P', '1', '1', '1'},
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1', '1', '1'}
};

float	get_slope(float angle)
{
	float radianAngle;


	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle == 90)
		return (INT32_MAX);
	if (angle == 270)
		return (INT32_MIN);
	radianAngle = (angle) * PI / 180.0;
	float dirx = cos(radianAngle);
	float diry = sin(radianAngle);
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

int	check_wall_hit(char dir, int step_x, int step_y, float angle)
{
	if (map[player_pos_y + step_y][player_pos_x + step_x] == '1')
		return (1);
	return (0);
}

float	calc_distance(float m, float angle)
{
	float	dist_x;
	float	dist_y;

	float		stepcount_x = 0;
	float		stepcount_y = 0;

	float		step_dir_y;
	float		step_dir_x;

	if (angle >= 0 && angle <= 180)
		step_dir_y = -1;
	else
		step_dir_y = 1;
	if (angle >= 90 && angle <= 270)
		step_dir_x = -1;
	else
		step_dir_x = 1;

	while(1)
	{
		dist_x =  calc_sx_sy(m, 'x');
		dist_y = calc_sx_sy(m, 'y');
		while (dist_x >= dist_y)
		{
			int	test = check_wall_hit('y', stepcount_x, stepcount_y, angle);
			if (test == 1)
				return ((stepcount_y - step_dir_y) * calc_sx_sy(m , 'y'));
			stepcount_y += step_dir_y;
			dist_y += calc_sx_sy(m, 'y');
			test = check_wall_hit('y', stepcount_x, stepcount_y, angle);
			if (test == 1)
				return ((stepcount_y - step_dir_y)* calc_sx_sy(m , 'y'));
		}
		while (dist_y > dist_x)
		{
			int	test = check_wall_hit('x', stepcount_x, stepcount_y, angle);
			if (test == 1)
				return ((stepcount_x - step_dir_x) * calc_sx_sy(m, 'x'));
			stepcount_x += step_dir_x;
			dist_x += calc_sx_sy(m, 'x');
			test = check_wall_hit('x', stepcount_x, stepcount_y, angle);
			if (test == 1)
				return ((stepcount_x - step_dir_x)* calc_sx_sy(m, 'x'));
		}
	}
}

int	main()
{
	float angle = 45;
	float m  = get_slope(angle);
	if (m < 0)
		m = -m;
	printf("%f\n", m);
	float dist = calc_distance(m, angle);
	if (dist < 0)
		dist *= -1;
	printf("Distance: %f\n", dist);
}
