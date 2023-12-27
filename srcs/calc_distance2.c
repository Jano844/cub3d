/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/27 13:57:55 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define WIDTH 7
#define HEIGHT 7

float	end_dist(float m, float angle, float playerx, float playery);

float	player_pos_x = 3;
float	player_pos_y = 2.5;

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

int	aufrunden(float num)
{
	float	temp;

	if (num >= 0)
	{
		temp = num - (int)num;
		if (temp == 0)
			return (num);
		temp = 1 - temp;
		return (num + temp);
	}
	num = fabs(num);
	temp = num - (int)num;
	if (temp == 0)
		return (-num);
	temp = 1 - temp;
	return (-(num + temp));
}

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

// float	calc_sx_sy(float m, char dir, float multiplier)
// {
// 	multiplier *= 10;
// 	if (multiplier == 0)
// 		multiplier == 10;
// 	if (dir == 'y')
// 	{
// 		if (m == 0)
// 			return(INT32_MAX);
// 		m = 1/m;
// 	}
// 	return (sqrt(1 + pow(m, 2)));
// }

// int	check_wall_hit(char dir, int step_x, int step_y, float playerx, float playery, float angle)
// {
// 	if (map[(int)playery + step_y][(int)playerx + step_x] == '1')
// 	{
// 		printf("Wall hit: %d   %d\n", (int)playery + step_y, (int)playerx + step_x);
// 		return (1);
// 	}
// 	return (0);
// }

// float	calc_distance(float m, float angle, float playerx, float playery)
// {
// 	float	dist_x;
// 	float	dist_y;

// 	float	stepcount_x = 0;
// 	float	stepcount_y = 0;

// 	float	step_dir_y;
// 	float	step_dir_x;

// 	if (angle >= 0 && angle <= 180)
// 		step_dir_y = -1;
// 	else
// 		step_dir_y = 1;
// 	if (angle >= 90 && angle <= 270)
// 		step_dir_x = -1;
// 	else
// 		step_dir_x = 1;


// 	dist_x =  calc_sx_sy(m, 'x');
// 	dist_y = calc_sx_sy(m, 'y');
// 	while(1)
// 	{
// 		while (dist_x >= dist_y)
// 		{
// 			if (check_wall_hit('y', stepcount_x, stepcount_y, playerx, playery, angle))
// 			{
// 				float	tempx = playerx + fabs(stepcount_x);
// 				float	tempy = playery + fabs(stepcount_y);
// 				return ((fabs(stepcount_y - step_dir_y) * calc_sx_sy(m , 'y')) + end_dist(m, angle, tempx, tempy)); //  + startdist(m, angle, &tempx, &tempy)
// 			}
// 			stepcount_y += step_dir_y;
// 			dist_y += calc_sx_sy(m, 'y');
// 			if (check_wall_hit('y', stepcount_x, stepcount_y, playerx, playery, angle))
// 			{
// 				float	tempx = playerx + fabs(stepcount_x);
// 				float	tempy = playery + fabs(stepcount_y);
// 				// printf("tempx = %f  tempy = %f\n", tempx, tempy);
// 				printf("Distance 2: %f\n", fabs(stepcount_y - step_dir_y) * calc_sx_sy(m , 'y'));
// 				return ((fabs(stepcount_y - step_dir_y) * calc_sx_sy(m , 'y')) + end_dist(m, angle, tempx, tempy));
// 			}
// 		}
// 		while (dist_y > dist_x)
// 		{
// 			if (check_wall_hit('x', stepcount_x, stepcount_y, playerx, playery, angle))
// 			{
// 				float	tempx = playerx + fabs(stepcount_x);
// 				float	tempy = playery + fabs(stepcount_y);
// 				return ((fabs(stepcount_x - step_dir_x) * calc_sx_sy(m , 'x')) + end_dist(m, angle, tempx, tempy));
// 			}
// 			stepcount_x += step_dir_x;
// 			dist_x += calc_sx_sy(m, 'x');
// 			if (check_wall_hit('y', stepcount_x, stepcount_y, playerx, playery, angle))
// 			{
// 				float	tempx = playerx + fabs(stepcount_x);
// 				float	tempy = playery + fabs(stepcount_y);
// 				// printf("tempx = %f  tempy = %f\n", tempx, tempy);
// 				printf("Distance 2: %f\n", fabs(stepcount_x - step_dir_x) * calc_sx_sy(m , 'x'));
// 				return ((fabs(stepcount_x - step_dir_x) * calc_sx_sy(m , 'x')) + end_dist(m, angle, tempx, tempy));
// 			}
// 		}
// 	}
// }

// float	calc_distance(float m, float angle, float playerx, float playery)
// {
// 	float	dist;

// 	dist = 0;
// 	while (map[(int)playery][(int)playery] != 1)
// 	{
// 		dist += fabs(startdist(m, angle, &playerx, &playery));
// 	}

// }

float	end_dist(float m, float angle, float playerx, float playery)
{
	float distx;
	float disty;

	// if (playery - (int)playery == 0 && playerx - (int)playerx == 0)
	// 	return (0);
	disty =  1 - (playery - (int)playery);
	distx = 1 - (playerx - (int)playerx);
	if (angle >= 0 && angle <= 180)
		disty = 1 - disty;
	if (angle >= 90 && angle <= 270)
		distx = 1 - distx;

	distx *= 10;
	disty *= 10;

	float tempx = (distx * sqrt(1 + pow(m, 2))) / 10;
	float tempy = (disty * sqrt(1 + pow(1/m, 2))) / 10;
	if (m == 0)
		return (tempx);
	if (playerx > playery)
	{
		printf("Distance 3: %f\n", tempx);
		return (tempx);
	}
	printf("Distance 3: %f\n", tempy);
	return (tempy);
}

float	startdist(float m, float angle, float *playerx, float *playery)
{
	float distx;
	float disty;

	// if (*playery - (int)*playery == 0 || *playerx - (int)*playerx == 0)
	// 	return (0);
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
	// printf("%f  %f\n", tempx, tempy);
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

	// printf("gegen: %f  an: %f\n", gegen, an);
	rad_angle = atan2(gegen, an);
	deg_angle = (rad_angle * 180) / PI;
	if (deg_angle < 0)
		deg_angle = 360 + deg_angle;
	// printf("%f\n", deg_angle);
	return(deg_angle);
}

int	main(int argc, char **argv)
{
	float	angle = atof(argv[1]);
	float	dist = 0;
	float	m;
	float	playerx = 2;
	float	playery = 2;
	float phi1 = get_phi(playery - 1, WIDTH - (playerx + 1));
	float phi2 = get_phi(-(HEIGHT - (playery + 1)), -(playerx - 1));
	while (angle >= 360)
		angle -= 360;


	m = fabs(get_slope(angle));
	// dist = fabs(startdist(m, angle, &playerx, &playery));
	// printf("%f  %f\n", playerx, playery);
	// printf("Distance 1: %f\n", fabs(dist));
	// dist = fabs(startdist(m, angle, &playerx, &playery));
	// printf("%f  %f\n", playerx, playery);
	// printf("Distance 1: %f\n", fabs(dist));

	int i = -1;
	int	tempy = playery;
	int	tempx = playerx;
	float last_dist = dist;
	while (map[tempy][tempx] != '1')
	{
		if (map[tempy][tempx] == '1')
			break ;
		last_dist = dist;
		dist += fabs(startdist(m, angle, &playerx, &playery));
		// printf("%f\n", dist);
		// printf("%d  %d\n", (int)playery, (int)playerx);
		tempy = playery;
		tempx = playerx;
		if (map[tempy][tempx] == '1')
			break ;
		// printf("%c\n", map[tempy][tempx]);
	}

	if (angle > phi1 && angle < phi2)
		dist = last_dist;
	// get_phi(playery, playerx);
	// if (tempx == 0 || tempy == 0)
	// 	dist = last_dist;
	// wenn nach oben oder links geguckt wird dist - 1/cos(angle)
	// dist += fabs(calc_distance(m, angle, playerx, playery));
	printf("result Distance: %f\n", fabs(dist));
}
