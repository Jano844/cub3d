/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2024/01/04 16:39:53 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_img_two(t_data *data)
{
	if (ft_open_image(data, &data->img->img_game_cursor, "textures/cross.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_wall,
			"textures/brick_small.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_portal,
			"textures/brick_portal_small.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_door_closed,
			"textures/brick_door_closed_small.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_door_open,
			"textures/brick_door_open_small.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_wall_shadow,
			"textures/brick_shadow_small.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_player, "textures/player.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_pistol[0], "textures/pistol/00.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_pistol[1], "textures/pistol/01.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_pistol[2], "textures/pistol/02.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_pistol[3], "textures/pistol/03.png"))
		return (1);
	if (ft_open_image(data, &data->img->img_pistol[4], "textures/pistol/04.png"))
		return (1);
	return (0);
}

int	init_img_one(t_data *data)
{
	if (ft_open_image_plus_info(data, &data->img->img_NO, &data->img->col_NO,
			data->game->NO))
		return (1);
	if (ft_open_image_plus_info(data, &data->img->img_SO, &data->img->col_SO,
			data->game->SO))
		return (1);
	if (ft_open_image_plus_info(data, &data->img->img_WE, &data->img->col_WE,
			data->game->WE))
		return (1);
	if (ft_open_image_plus_info(data, &data->img->img_EA, &data->img->col_EA,
			data->game->EA))
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
				data->player->start_direction = data->game->map[i][j];
				data->game->map[i][j] = 'P';
				data->player->x = pixel_x;
				data->player->y = pixel_y;
				return ;
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
	data->player->view_angle = 80;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	data->player->prev_mouseX = (float)x;
}
