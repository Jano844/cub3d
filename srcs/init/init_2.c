/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2024/01/13 13:54:00 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	ft_check_all_imgs(t_data *data)
{
	int	i;

	i = 0;
	if (!data->img->img_player || !data->img->img_mm_wall
		|| !data->img->img_mm_walk || !data->img->img_splash_main
		|| !data->img->img_splash_start)
		return (1);
	while (i < 6)
	{
		if (i < 5 && !data->img->img_pistol[i])
			return (1);
		if (!data->img->img_torch[i])
			return (1);
		i++;
	}
	return (0);
}

int	init_img_two(t_data *data)
{
	ft_open_image(data, &data->img->img_mm_wall,
		"textures/minimap/brick_wall.png");
	ft_open_image(data, &data->img->img_mm_walk,
		"textures/minimap/brick_walk.png");
	ft_open_image(data, &data->img->img_player, "textures/player.png");
	ft_open_image(data, &data->img->img_pistol[0], "textures/weapon/0.png");
	ft_open_image(data, &data->img->img_pistol[1], "textures/weapon/1.png");
	ft_open_image(data, &data->img->img_pistol[2], "textures/weapon/2.png");
	ft_open_image(data, &data->img->img_pistol[3], "textures/weapon/3.png");
	ft_open_image(data, &data->img->img_pistol[4], "textures/weapon/4.png");
	ft_open_image(data, &data->img->img_torch[0], "textures/torch/0.png");
	ft_open_image(data, &data->img->img_torch[1], "textures/torch/1.png");
	ft_open_image(data, &data->img->img_torch[2], "textures/torch/2.png");
	ft_open_image(data, &data->img->img_torch[3], "textures/torch/3.png");
	ft_open_image(data, &data->img->img_torch[4], "textures/torch/4.png");
	ft_open_image(data, &data->img->img_torch[5], "textures/torch/5.png");
	ft_open_image_splash(data);
	if (ft_check_all_imgs(data))
		return (1);
	return (0);
}

int	init_img_one(t_data *data)
{
	if (ft_open_image_keep_text(data, &data->img->img_no, \
			&data->img->txt_no, data->game->no)
		* ft_open_image_keep_text(data, &data->img->img_so, \
			&data->img->txt_so, data->game->so)
		* ft_open_image_keep_text(data, &data->img->img_we, \
			&data->img->txt_we, data->game->we)
		* ft_open_image_keep_text(data, &data->img->img_ea, \
			&data->img->txt_ea, data->game->ea) == 0)
		return (1);
	return (0);
}

void	init_coords(t_data *data, int pixel_x, int pixel_y)
{
	int	i;
	int	j;

	i = 0;
	while (data->game->map[i])
	{
		j = 0;
		while (data->game->map[i][j])
		{
			if (data->game->map[i][j] == 'N' || data->game->map[i][j] == 'E'
				|| data->game->map[i][j] == 'S' || data->game->map[i][j] == 'W')
			{
				data->game->count_player++;
				data->player->start_direction = data->game->map[i][j];
				data->game->map[i][j] = 'P';
				data->player->x = pixel_x;
				data->player->y = pixel_y;
			}
			pixel_x += 1;
			j++;
		}
		pixel_x = 0;
		pixel_y += 1;
		i++;
	}
}

void	init_player(t_data *data)
{
	int32_t	x;
	int32_t	y;

	if (data->player->start_direction == 'N')
		data->player->angle = 90;
	if (data->player->start_direction == 'E')
		data->player->angle = 0;
	if (data->player->start_direction == 'S')
		data->player->angle = 270;
	if (data->player->start_direction == 'W')
		data->player->angle = 180;
	data->player->view_angle = 60;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	data->player->prev_mouse_x = (float)x;
}
