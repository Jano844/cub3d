/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:48:00 by slippert          #+#    #+#             */
/*   Updated: 2024/01/12 18:58:05 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// if (data->game->map[y][x] == '5' && is_wall)
// {
// 	mlx_image_to_window(data->mlx, data->img->img_mm_door_open, x * 16, y
// 		* 16);
// 	data->minimap->map[y][x] = mlx_image_to_window(data->mlx,
// 			data->img->img_mm_door_closed, x * 16, y * 16);
// }
// else if (data->game->map[y][x] == '9' && is_wall)
// 	mlx_image_to_window(data->mlx, data->img->img_mm_portal, x * 16, y
// 		* 16);
// else
static void	draw_objects_helper(t_data *data, int is_wall, int y, int x)
{
	if (data->game->map[y][x] == 'P' && !is_wall)
		mlx_image_to_window(data->mlx, data->img->img_player, data->player->x
			* 16, data->player->y * 16);
}

static void	draw_quadrat(t_data *data, int start_x, int start_y)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = ft_pixel(32, 32, 32, 255);
	y = 0;
	while (y < 16)
	{
		x = 0;
		while (x < 16)
		{
			mlx_put_pixel(data->img->img_mm_overlay, (start_x * 16) + x,
				(start_y * 16) + y, color);
			data->game->pixel_unexp++;
			x++;
		}
		y++;
	}
}

static void	draw_objects(t_data *data, int is_wall)
{
	int	x;
	int	y;

	y = 0;
	while (data->game->map[y])
	{
		x = 0;
		while (data->game->map[y][x])
		{
			if (data->game->map[y][x] != ' ' && is_wall)
				draw_quadrat(data, x, y);
			if (data->game->map[y][x] == '1' && is_wall)
				mlx_image_to_window(data->mlx, data->img->img_mm_wall, x * 16, y
					* 16);
			else if (is_wall && (data->game->map[y][x] == '0' \
					|| data->game->map[y][x] == 'P'))
				mlx_image_to_window(data->mlx, data->img->img_mm_walk, x
					* 16, y * 16);
			else
				draw_objects_helper(data, is_wall, y, x);
			x++;
		}
		y++;
	}
}

// while (i < data->img->img_mm_door_open->count)
// 	data->img->img_mm_door_open->instances[i++].z = 1;
static void	set_z(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->img->img_mm_walk->count)
		data->img->img_mm_walk->instances[i++].z = 1;
	i = 0;
	data->img->img_player->instances[0].z = 2;
}

void	draw_minimap(t_data *data)
{
	draw_objects(data, 0);
	draw_objects(data, 1);
	set_z(data);
}
