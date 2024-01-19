/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 21:22:27 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/18 16:41:26 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_floor_ceiling(t_data *data, t_dda *dda)
{
	float	start;

	start = -1;
	while (++start < dda->line_top)
		mlx_put_pixel(data->img->img_game, dda->j, start,
			ft_shadow_coloring(data, start, data->game->col_ceiling, false));
	start = dda->line_bottom - 1;
	if (start < 0)
		start = 0;
	while (++start < data->height)
		mlx_put_pixel(data->img->img_game, dda->j, start,
			ft_shadow_coloring(data, start, data->game->col_floor, true));
}

void	draw_wall(t_data *data, t_dda *dda, int block_width,
			float temp_bottom_top_y[3])
{
	float	block_height;

	if (temp_bottom_top_y[2] < 0)
		temp_bottom_top_y[2] = 0;
	while (temp_bottom_top_y[2] < dda->line_bottom)
	{
		block_height = calc_for_x(temp_bottom_top_y[1] - temp_bottom_top_y[0],
				temp_bottom_top_y[2] - temp_bottom_top_y[0]);
		mlx_put_pixel(data->img->img_game, dda->j, temp_bottom_top_y[2],
			ft_select_color(data, dda, block_height, block_width));
		temp_bottom_top_y[2]++;
	}
}

void	draw_vertical(t_data *data, t_dda *dda, bool if_true, int block_width)
{
	float			y;
	static float	temp_if_true;
	float			temp_bottom_top_y[3];

	dda->tmp = round(dda->distance * cos((fabs(dda->angle)) * PI / 180) * 1000)
		/ 1000;
	if (if_true == true && temp_if_true < dda->tmp)
		dda->tmp = temp_if_true;
	dda->line_bottom = (data->height / 2) + (SIZE * dda->treshold / dda->tmp);
	dda->line_top = (data->height / 2) - (SIZE * dda->treshold / dda->tmp);
	temp_bottom_top_y[0] = dda->line_top;
	temp_bottom_top_y[1] = dda->line_bottom;
	if (dda->line_top < 0)
		dda->line_top = 0;
	if (dda->line_bottom >= data->height)
		dda->line_bottom = data->height;
	y = dda->line_top;
	temp_bottom_top_y[2] = y;
	draw_wall(data, dda, block_width, temp_bottom_top_y);
	draw_floor_ceiling(data, dda);
	temp_if_true = dda->tmp;
}

void	dda_vertical(t_data *data, t_dda *dda, bool if_true)
{
	int	x_dir;
	int	block_width;

	x_dir = 0;
	block_width = ft_get_block_width(dda);
	while (x_dir < QUALITY)
	{
		draw_vertical(data, dda, if_true, block_width);
		x_dir++;
		if (x_dir < QUALITY)
			dda->j++;
	}
}
