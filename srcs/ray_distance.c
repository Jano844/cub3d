/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:45:14 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/17 23:37:13 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float calculateDistanceToWall(t_data *data, float dirX, float dirY)
{
	float stepSize = 0.00001;
	float distance;
	float currentX = data->player->x;
	float currentY = data->player->y;

	printf("%f\n", currentX);
	printf("%f\n", currentY);
	while (data->map->map[(int)currentY][(int)currentX] != '1')
	{
		if (data->map->map[(int)currentY][(int)currentX] == '\0'
			|| data->map->map[(int)currentY] == NULL)
			return (-1);
		currentX += stepSize * dirX;
		currentY += stepSize * dirY;
	}
	distance = sqrt((currentX - data->player->x) * (currentX - data->player->x)
		 + (currentY - data->player->y) * (currentY - data->player->y));
	return (distance);
}


void	calculateDirection(float angle, float dir[2])
{
	float radianAngle;

	while (angle > 360)
		angle -= 360;
	radianAngle = (angle) * PI / 180.0;
	dir[0] = cos(radianAngle);
	dir[1] = sin(radianAngle);
}

float ray_distance(t_data *data)
{
	float dir[2];

	calculateDirection(data->player->angle, dir);
	return (calculateDistanceToWall(data, dir[0], dir[1]));
}
