/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_detection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2024/01/07 10:28:35 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_coords_helper(t_data *data, t_draw_rays *ray,
	int ray_len, int increment)
{
	if (data->player->dir.sideward != 0 && data->player->dir.forward == 1)
	{
		if (data->player->dir.sideward == -1 && data->player->dir.forward == 1)
			increment = 1;
		ray->x_coord = data->player->x * 16 + 8 + ray_len
			* cos((-data->player->angle + ray->angle_offset
					- (45 * increment)) * PI / 180);
		ray->y_coord = data->player->y * 16 + 8 + ray_len
			* sin((-data->player->angle + ray->angle_offset
					- (45 * increment)) * PI / 180);
	}
	else if (data->player->dir.sideward != 0 && data->player->dir.forward == -1)
	{
		if (data->player->dir.sideward == -1 && data->player->dir.forward == -1)
			increment = 1;
		ray->x_coord = data->player->x * 16 + 8 + ray_len
			* cos((-data->player->angle + ray->angle_offset
					+ (45 * increment) + (180 * increment)) * PI / 180);
		ray->y_coord = data->player->y * 16 + 8 + ray_len
			* sin((-data->player->angle + ray->angle_offset
					+ (45 * increment) + (180 * increment)) * PI / 180);
	}
}

void	set_coords(t_data *data, t_draw_rays *ray, int ray_len)
{
	int	increment;

	increment = -1;
	if (data->player->dir.forward != 0 && data->player->dir.sideward == 0)
	{
		ray->x_coord = data->player->x * 16 + 8
			+ (ray_len * data->player->dir.forward)
			* cos((-data->player->angle + ray->angle_offset) * PI / 180);
		ray->y_coord = data->player->y * 16 + 8
			+ (ray_len * data->player->dir.forward)
			* sin((-data->player->angle + ray->angle_offset) * PI / 180);
	}
	else if (data->player->dir.sideward != 0 && data->player->dir.forward == 0)
	{
		ray->x_coord = data->player->x * 16 + 8
			+ (ray_len * data->player->dir.sideward)
			* cos((-data->player->angle + ray->angle_offset + 90) * PI / 180);
		ray->y_coord = data->player->y * 16 + 8
			+ (ray_len * data->player->dir.sideward)
			* sin((-data->player->angle + ray->angle_offset + 90) * PI / 180);
	}
	else
		set_coords_helper(data, ray, ray_len, increment);
}
