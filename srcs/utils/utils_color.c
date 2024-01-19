/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/17 19:43:38 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	ft_shadow_coloring(t_data *data, float start, int src_color,
		bool is_floor)
{
	double	brightness;

	if (data->is_shooting)
		return (src_color);
	if ((is_floor && start - 30 < 512) || (!is_floor && start + 30 > 512))
		return (ft_pixel(0, 0, 0, 255));
	if (is_floor)
		brightness = -((float)(512 - start) / 512);
	else
		brightness = 1.0f - (float)(start) / 512;
	return (ft_pixel(((src_color >> 24) & 0xFF) * brightness,
			((src_color >> 16) & 0xFF) * brightness, ((src_color >> 8) & 0xFF)
			* brightness, (src_color & 0xFF)));
}

static int	ft_text_color(mlx_texture_t *text, t_dda *dda, int block_width,
		int block_height)
{
	int		pos;
	double	brightness;

	if (block_width < 0)
		block_width = 0;
	if (block_height < 0)
		block_height = 0;
	if ((uint32_t)block_width >= text->width)
		block_width = text->width - 1;
	if ((uint32_t)block_height >= text->height)
		block_height = text->height - 1;
	pos = text->bytes_per_pixel * (block_height + text->width * block_width);
	brightness = fmax(1.0 - (dda->distance / dda->shadow), 0);
	if (dda->distance > dda->shadow)
		return (255);
	return (ft_pixel((int)(text->pixels[pos] * brightness), \
			(int)(text->pixels[pos + 1] * brightness), \
			(int)(text->pixels[pos + 2] * brightness), \
			(int)text->pixels[pos + 3]));
}

uint32_t	ft_select_color(t_data *data, t_dda *dda, int block_height,
		int block_width)
{
	if (data->is_shooting)
		dda->shadow = 100;
	else if (data->is_torching)
		dda->shadow = 11 * 1.75f;
	if (data->wall_type == 'W')
	{
		if (dda->direction == 'N')
			dda->color_wall = ft_text_color(data->img->txt_no, dda,
					block_height, block_width);
		else if (dda->direction == 'E')
			dda->color_wall = ft_text_color(data->img->txt_ea, dda,
					block_height, block_width);
		else if (dda->direction == 'S')
			dda->color_wall = ft_text_color(data->img->txt_so, dda,
					block_height, block_width);
		else if (dda->direction == 'W')
			dda->color_wall = ft_text_color(data->img->txt_we, dda,
					block_height, block_width);
	}
	return (dda->color_wall);
}
