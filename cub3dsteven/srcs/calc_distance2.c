/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/04 21:47:11 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	get_slope(float angle)
{
	float	radianAngle;

	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle == 90)
		return (FLT_MAX);
	if (angle == 270)
		return (-FLT_MAX);
	radianAngle = angle * PI / 180.0;
	return (tan(radianAngle));
}

float	startdist(float m, float angle, float *playerx, float *playery,
		char *dir, bool *xminus, bool *yminus)
{
	float	distx;
	float	disty;
	float	tempx;
	float	tempy;

	disty = 1 - (*playery - (int)*playery);
	distx = 1 - (*playerx - (int)*playerx);
	if (angle >= 0 && angle <= 180)
		disty = 1 - disty;
	if (disty == 0)
		disty = 1;
	if (angle >= 90 && angle <= 270)
		distx = 1 - distx;
	if (distx == 0)
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
	tempx = (distx * sqrt(1 + pow(m, 2))) / 10;
	tempy = (disty * sqrt(1 + pow(1 / m, 2))) / 10;
	if (m == 0)
		return (tempx);
	if (tempx < tempy)
	{
		if (angle >= 90 && angle <= 270)
		{
			*xminus = true;
			*playerx -= distx / 10;
			*dir = 'W';
		}
		else
		{
			*playerx += distx / 10;
			*dir = 'E';
		}
		if (angle >= 0 && angle <= 180)
		{
			*yminus = true;
			*playery -= sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		}
		else
			*playery += sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		return (tempx);
	}
	if (angle >= 0 && angle <= 180)
	{
		*yminus = true;
		*playery -= disty / 10;
		*dir = 'N';
	}
	else
	{
		*playery += disty / 10;
		*dir = 'S';
	}
	if (angle >= 90 && angle <= 270)
	{
		*xminus = true;
		*playerx -= sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	}
	else
		*playerx += sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	return (tempy);
}

float	calc_distance(float angle, float playerx, float playery, t_data *data,
		char *dir, bool *new_block)
{
	static char	old_dir;
	float	dist;
	int		tempy;
	int		tempx;
	float	last_dist;
	float	m;
	char	last_dir;
	bool	xmin;
	bool	ymin;

	dist = 0;
	tempy = playery;
	tempx = playerx;
	last_dist = dist;
	m = fabs(get_slope(angle));
	while (!ft_is_in_set(data->game->map[tempy][tempx], "159"))
	{
		ymin = false;
		xmin = false;
		tempy = playery;
		tempx = playerx;
		last_dist = dist;
		last_dir = *dir;
		if (!data->game->map[tempy][tempx] || !data->game->map[tempy])
			return (1);
		dist += fabs(startdist(m, angle, &playerx, &playery, dir, &xmin,
					&ymin));
		tempy = playery;
		tempx = playerx;
		if (xmin == true && ymin == true)
		{
			tempx = ceil(playerx) - 1;
			tempy = ceil(playery) - 1;
		}
		else
		{
			if (xmin == true)
				tempx = ceil(playerx) - 1;
			if (ymin == true)
				tempy = ceil(playery) - 1;
		}
	}
	if (data->game->map[tempy][tempx] == 'L')
		*new_block = false;
	if (data->game->map[tempy][tempx] == '1' || *dir != old_dir)
	{
		data->game->map[tempy][tempx] = 'L';
		*new_block = true;
	}
	if (data->game->map[tempy][tempx] == '5')
		data->wall_type = 'D';
	else if (data->game->map[tempy][tempx] == '9')
		data->wall_type = 'P';
	old_dir = *dir;
	return (fabs(dist));
}

float	calc_dist(t_data *data, float angle, char *dir, bool *new_block)
{
	float	playerx;
	float	playery;

	playerx = data->player->x + 0.5f;
	playery = data->player->y + 0.5f;
	angle = data->player->angle + angle;
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return (calc_distance(angle, playerx, playery, data, dir, new_block));
}
