/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cross.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/07 15:38:00 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_hori(t_data *data, t_crosshair cross)
{
	cross.i = cross.middle_y - 1;
	cross.j = 0;
	while (cross.i < cross.middle_y + 1)
	{
		cross.j = cross.middle_x - 10;
		while (cross.j < cross.middle_x + 10)
		{
			if (cross.j < cross.middle_x - 3 || cross.j > cross.middle_x + 2)
				mlx_put_pixel(data->img->img_crosshair, cross.j, cross.i,
					cross.color);
			cross.j++;
		}
		cross.i++;
	}
}

void	draw_verti(t_data *data, t_crosshair cross)
{
	cross.i = cross.middle_x - 1;
	while (cross.i < cross.middle_x + 1)
	{
		cross.j = cross.middle_y - 10;
		while (cross.j < cross.middle_y + 10)
		{
			if (cross.j < cross.middle_y - 3 || cross.j > cross.middle_y + 2)
				mlx_put_pixel(data->img->img_crosshair, cross.i, cross.j,
					cross.color);
			cross.j++;
		}
		cross.i++;
	}
}

void	draw_leftdiagonal(t_data *data, t_crosshair cross)
{
	cross.middle_x = cross.tmp_middle_x;
	cross.i = cross.middle_y - 5;
	while (cross.i < cross.middle_y + 5)
	{
		cross.j = cross.middle_x - 6;
		while (cross.j < cross.middle_x - 3)
		{
			if (cross.j < cross.tmp_middle_x - 2 || cross.j > cross.tmp_middle_x
				+ 1)
				mlx_put_pixel(data->img->img_crosshair, cross.j, cross.i,
					cross.color);
			cross.j++;
		}
		cross.middle_x += 1;
		cross.i++;
	}
}

void	draw_rightdiagonal(t_data *data, t_crosshair cross)
{
	cross.middle_x = cross.tmp_middle_x;
	cross.i = cross.middle_y + 4;
	while (cross.i > cross.middle_y - 6)
	{
		cross.j = cross.middle_x - 6;
		while (cross.j < cross.middle_x - 3)
		{
			if (cross.j < cross.tmp_middle_x - 2 || cross.j > cross.tmp_middle_x
				+ 1)
				mlx_put_pixel(data->img->img_crosshair, cross.j, cross.i,
					cross.color);
			cross.j++;
		}
		cross.middle_x += 1;
		cross.i--;
	}
}

void	draw_circle(t_data *data, t_crosshair cross)
{
	cross.middle_x = cross.tmp_middle_x - 1;
	cross.i = cross.middle_y + cross.radius;
	while (cross.i >= cross.middle_y - cross.radius)
	{
		cross.j = cross.middle_x - cross.radius;
		while (cross.j <= cross.middle_x + cross.radius)
		{
			if (fabs(sqrt(pow(cross.j - cross.middle_x, 2) + pow(cross.i
							- cross.middle_y, 2)) - cross.radius) < 1.0)
				mlx_put_pixel(data->img->img_crosshair, cross.j, cross.i,
					cross.color);
			cross.j++;
		}
		cross.i--;
	}
}
