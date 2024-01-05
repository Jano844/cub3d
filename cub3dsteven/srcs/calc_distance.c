/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:45:14 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/29 13:14:35 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	calculate_distance_to_wall(t_data *data, float dirX, float dirY)
{
	float	stepSize;
	double	distance;
	float	currentX;
	float	currentY;
	int		X;
	int		Y;

	stepSize = 0.001;
	currentX = data->player->x;
	currentY = data->player->y;
	X = roundf(currentX);
	Y = roundf(currentY);
	while (!ft_is_in_set(data->game->map[Y][X], "159"))
	{
		if (!data->game->map[Y][X] || !data->game->map[Y])
			return (1);
		currentX += stepSize * dirX;
		currentY += stepSize * dirY;
		X = roundf(currentX);
		Y = roundf(currentY);
	}
	if (data->game->map[Y][X] == '5')
		data->wall_type = 'D';
	else if (data->game->map[Y][X] == '9')
		data->wall_type = 'P';
	distance = sqrt((currentX - data->player->x) * (currentX - data->player->x)
			+ (currentY - data->player->y) * (currentY - data->player->y));
	return (distance);
}

void	calculate_direction(float angle, float dir[2])
{
	float	radian_angle;

	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	radian_angle = (angle) * PI / 180.0;
	dir[0] = cos(radian_angle);
	dir[1] = sin(radian_angle);
}

double	ray_distance(t_data *data, float angle)
{
	float	dir[2];

	calculate_direction(data->player->angle + angle, dir);
	return (calculate_distance_to_wall(data, dir[0], dir[1]));
}
