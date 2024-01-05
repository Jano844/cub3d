/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/04 16:10:11 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_img_info(t_data *data, mlx_texture_t *text, uint32_t **color)
{
	*color = get_color(text);
	data->wall_size[0] = text->width;
	data->wall_size[1] = text->height;
}

int	ft_open_image(t_data *data, mlx_image_t **img_direction, char *img_path)
{
	mlx_texture_t	*text;

	text = mlx_load_png(img_path);
	if (!text)
		return (1);
	*img_direction = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	return (0);
}

int	ft_open_image_plus_info(t_data *data, mlx_image_t **img_direction,
		uint32_t **color, char *img_path)
{
	mlx_texture_t	*text;

	text = mlx_load_png(img_path);
	if (!text)
		return (1);
	*img_direction = mlx_texture_to_image(data->mlx, text);
	init_img_info(data, text, color);
	mlx_delete_texture(text);
	return (0);
}
