/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2024/01/17 19:45:50 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_player_angle(double xpos, double ypos, void *param)
{
	t_data	*data;
	float	delta_x;
	float	new_angle;
	float	sensitivity;

	xpos = 0;
	ypos = 0;
	data = param;
	mlx_get_mouse_pos(data->mlx, &data->player->mouse_x,
		&data->player->mouse_y);
	delta_x = data->player->mouse_x - data->player->prev_mouse_x;
	sensitivity = 0.1;
	new_angle = delta_x * sensitivity;
	data->player->angle += -new_angle;
	data->player->prev_mouse_x = data->player->mouse_x;
}

void	ft_key_press(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		ft_change_item(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (data->is_torching)
			ft_change_item(data);
		data->is_shooting = true;
	}
	if (keydata.key == MLX_KEY_PAGE_UP && keydata.action == MLX_PRESS)
	{
		data->cross_index++;
		if (data->cross_index >= 9)
			data->cross_index = 0;
		draw_crosshair(data, data->cross_colors[data->cross_index]);
	}
	if (keydata.key == MLX_KEY_PAGE_DOWN && keydata.action == MLX_PRESS)
	{
		data->cross_index--;
		if (data->cross_index < 0)
			data->cross_index = 8;
		draw_crosshair(data, data->cross_colors[data->cross_index]);
	}
}

void	ft_mouse_press(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_data	*data;

	mods = 0;
	data = param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		if (!data->is_started)
			return (ft_splash_to_game(data));
		if (data->is_torching)
			ft_change_item(data);
		data->is_shooting = true;
	}
	if (button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_PRESS)
		ft_change_item(data);
}

static void	ft_key_hold_helper(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player->dir.sideward = -1;
		move_player(data, 0.05, 0);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player->dir.sideward = 1;
		move_player(data, -0.05, 0);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->angle -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->angle += 5;
	data->player->dir.forward = 0;
	data->player->dir.sideward = 0;
}

void	ft_key_hold(void *param)
{
	t_data		*data;

	data = param;
	data->player->dir.sideward = 0;
	data->player->dir.forward = 0;
	ft_memset(data->img->img_movement_ray->pixels, 0,
		data->img->img_movement_ray->width * data->img->img_movement_ray->height
		* sizeof(int32_t));
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player->dir.forward = 1;
		move_player(data, 0.05, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player->dir.forward = -1;
		move_player(data, -0.05, 1);
	}
	ft_key_hold_helper(data);
}
