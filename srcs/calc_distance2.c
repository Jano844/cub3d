/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/30 16:26:16 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

float	startdist(float m, float angle, float *playerx, float *playery, char *dir, bool	*xminus, bool *yminus)
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
		{
			*xminus = true;
			*playerx -= distx / 10;
		}
		else
			*playerx += distx / 10;
		return (distx / 10);
	}
	if (angle == 90 || angle == 270)
	{
		if (angle >= 0 && angle <= 180)
		{
			*yminus = true;
			*playery -= disty / 10;
		}
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
		{
			*xminus = true;
			*playerx -= distx / 10;
		}
		else
			*playerx += distx / 10;

		if (angle >= 0 && angle <= 180)
		{
			*yminus = true;
			*playery -= sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		}
		else
			*playery += sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		*dir = 'x';
		return (tempx);
	}
	if (angle >= 0 && angle <= 180)
	{
		*yminus = true;
		*playery -= disty / 10;
	}
	else
		*playery += disty / 10;

	if (angle >= 90 && angle <= 270)
	{
		*xminus = true;
		*playerx -= sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	}
	else
		*playerx += sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	*dir = 'y';
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

float	calc_distance(float angle, float playerx, float playery, t_data *data, char *dir)
{
	float	dist = 0;
	// float phiObenRechts = get_phi(playery - 1, data->map->width - (playerx + 1));
	// float phiObenLinks = get_phi(playery - 1, -(playerx - 1));
	// float phiUntenLinks = get_phi(-(data->map->height - (playery + 1)), -(playerx - 1));
	// float phiUntenRechts = get_phi(-(data->map->height - (playery + 1)), (playerx - 1));
	// int i = -1;
	int	tempy = playery;
	int	tempx = playerx;
	float last_dist = dist;
	float	m;
	char	last_dir;
	bool	xmin = false;
	bool	ymin = false;

	m = fabs(get_slope(angle));
	while (data->map->map[tempy][tempx] != '1')
	{
		ymin = false;
		xmin = false;
		tempy = playery;
		tempx = playerx;
		last_dist = dist;
		last_dir = *dir;
		if (data->map->map[tempy][tempx] == '1')
			break ;
		dist += fabs(startdist(m, angle, &playerx, &playery, dir, &xmin, &ymin));
		// printf("%.2f x: %d y: %d\n", dist, tempx, tempy);
		tempy = playery;
		tempx = playerx;
		if (xmin == true && ymin == true)
		{
			tempx = aufrunden(playerx) - 1;
			tempy = aufrunden(playery) - 1;
		}
		else
		{
			if (xmin == true)
				tempx = aufrunden(playerx) - 1;
			if (ymin == true)
				tempy = aufrunden(playery) - 1;
		}
		// printf("%.2f\n", dist);
		// printf("%d  %d\n", tempx, tempy);
		// printf("%.2f  %.2f\n", playerx, playery);
		if (data->map->map[tempy][tempx] == '1')
			break ;
	}
	// printf("angle %f dist %f last_dist %f dir %c\n", angle, dist, last_dist, *dir);
	// if ((angle > phiObenRechts && angle < phiObenLinks) && last_dir != 'x')
	// {
	// 	*dir = last_dir;
	// 	dist = last_dist;
	// }
	// if ((angle >phiObenLinks && angle < phiUntenLinks) && last_dir != 'y') //
	// {
	// 	*dir = last_dir;
	// 	dist = last_dist;
	// }
	// printf("%f  %f\n", dist, angle);
	// printf("angle %f dist %f last_dist %f dir %c\n", angle, dist, last_dist, *dir);
	// printf("OL: %.1f OR:%.1f\nUL: %.1f UR: %.1f\n", phiObenLinks, phiObenRechts, phiUntenLinks, phiUntenRechts);
	return (fabs(dist));
}


float	calc_dist(t_data *data, float angle, char *dir)
{
	float	playerx = data->player->x;
	float	playery = data->player->y;

	angle = data->player->angle + angle;
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return(calc_distance(angle, playerx, playery, data, dir));
}
