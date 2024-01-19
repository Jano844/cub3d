/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2024/01/13 14:37:48 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	init_helper(t_data *data, char *input)
{
	if (init_map(data, input))
		return (1);
	if (data->game->width * SIZE < 1920)
		data->width = data->game->width * SIZE;
	else
		data->width = 1920;
	if (data->game->height * SIZE < 1080)
		data->height = data->game->height * SIZE;
	else
		data->height = 1080;
	data->height = 1024;
	data->width = 1024;
	data->game->count_player = 0;
	return (0);
}

static int	init_minimap(t_data *data)
{
	data->minimap->width = data->game->width;
	data->minimap->height = -1;
	data->minimap->map = ft_calloc((data->height + 1), sizeof(int *));
	if (!data->minimap->map)
		return (ft_error("Error: data->minimap->map allocation failed!"));
	while (++data->minimap->height < data->height)
	{
		data->minimap->map[data->minimap->height] = ft_calloc((data->height
					+ 1), sizeof(int));
		if (!data->minimap->map[data->minimap->height])
			return (\
			ft_free2d_until((void *)data->minimap->map, data->minimap->height), \
			ft_error("Error: data->minimap->map allocation failed!"));
	}
	return (0);
}

static void	init_cross_colors(t_data *data)
{
	data->cross_index = 0;
	data->cross_colors[0] = ft_pixel(255, 255, 255, 125);
	data->cross_colors[1] = ft_pixel(4, 222, 222, 125);
	data->cross_colors[2] = ft_pixel(140, 0, 255, 125);
	data->cross_colors[3] = ft_pixel(0, 255, 221, 125);
	data->cross_colors[4] = ft_pixel(0, 119, 255, 125);
	data->cross_colors[5] = ft_pixel(43, 255, 0, 125);
	data->cross_colors[6] = ft_pixel(255, 29, 0, 125);
	data->cross_colors[7] = ft_pixel(255, 99, 71, 125);
	data->cross_colors[8] = ft_pixel(0, 0, 0, 0);
}

static int	init_win_imgs(t_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "cub3D", false);
	if (!data->mlx)
		return (ft_error("Error: mlx_init failed!"));
	data->img->img_game = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img->img_game)
		return (ft_error("Error: img_game creation failed!"));
	data->img->img_player_ray = mlx_new_image(data->mlx, data->game->width * 16,
			data->game->height * 16);
	if (!data->img->img_player_ray)
		return (ft_error("Error: img_player_ray creation failed!"));
	data->img->img_movement_ray = mlx_new_image(data->mlx, data->game->width
			* 16, data->game->height * 16);
	if (!data->img->img_movement_ray)
		return (ft_error("Error: img_movement_ray creation failed!"));
	data->img->img_mm_overlay = mlx_new_image(data->mlx, data->game->width * 16,
			data->game->height * 16);
	if (!data->img->img_mm_overlay)
		return (ft_error("Error: img_mm_overlay creation failed!"));
	data->img->img_crosshair = mlx_new_image(data->mlx, 255, 255);
	if (!data->img->img_crosshair)
		return (ft_error("Error: img_crosshair creation failed!"));
	return (0);
}

int	ft_init(t_data *data, char *input)
{
	if (init_helper(data, input))
		return (1);
	if (init_win_imgs(data))
		return (1);
	if (init_img_one(data) || init_img_two(data))
		return (ft_error("Error: failed to read .png file!"));
	init_cross_colors(data);
	if (init_minimap(data))
		return (1);
	init_coords(data, 0, 0);
	if (data->game->count_player != 1)
		return (ft_error("Error: to few or many players!"));
	init_player(data);
	return (0);
}
