/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:01:57 by slippert          #+#    #+#             */
/*   Updated: 2024/01/12 10:50:08 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	get_slope(float angle)
{
	float	radian_angle;

	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle == 90)
		return (FLT_MAX);
	if (angle == 270)
		return (-FLT_MAX);
	radian_angle = angle * PI / 180.0;
	return (tan(radian_angle));
}

float	calc_for_x(float big, float small)
{
	float	x;

	x = fabs(((small) / big) * 64);
	return (x);
}

void	reset_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->game->map_dda[y] != NULL)
	{
		x = 0;
		while (data->game->map_dda[y][x] != '\0')
		{
			data->game->map_dda[y][x] = data->game->map[y][x];
			x++;
		}
		y++;
	}
}

float	ft_get_block_width(t_dda *calc)
{
	int	i;
	int	block_width;

	i = 0;
	block_width = 0;
	while (calc->width_array[i] < calc->j)
	{
		i++;
		if (calc->width_array[i] != (float)0 && calc->width_array[i] < FLT_MAX)
		{
			block_width = (int)calc_for_x(calc->width_array[i] \
			- calc->width_array[i - 1], calc->j - calc->width_array[i - 1]);
		}
	}
	return (block_width);
}
