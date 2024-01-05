/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2024/01/04 17:12:59 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	move_player(t_data *data, float speed, int forward, const char *set)
{
	float	radian_angle;
	float	p_x_cos;
	float	p_y_sin;

	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
	{
		if (speed > 0)
			speed += 0.15f;
		else
			speed -= 0.15f;
	}
	if (forward == 1)
		radian_angle = data->player->angle * PI / 180.0;
	else
		radian_angle = (data->player->angle + 90.0) * PI / 180.0;
	if (check_for_wall(data, speed, radian_angle, set) || (speed > 0.0f
			&& check_wall_corner_ahead(data, set)) || (speed < 0.0f
			&& check_wall_corner_behind(data, set)))
		return ;
	p_x_cos = speed * cos(radian_angle);
	p_y_sin = speed * sin(radian_angle);
	data->player->x += p_x_cos;
	data->player->y -= p_y_sin;
	data->img->img_player->instances[0].x = data->player->x * 16;
	data->img->img_player->instances[0].y = data->player->y * 16;
}

// Calculate the difference in X position between
// the current and previous mouse position
// Use this difference to update the player's angle
// Update the player's angle
// Save the current mouse position as
// the previous mouse position for the next frame
void	update_player_angle(double xpos, double ypos, void *param)
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
	delta_x = data->player->mouse_x - data->player->prev_mouseX;
	sensitivity = 0.1;
	new_angle = delta_x * sensitivity;
	data->player->angle += -new_angle;
	data->player->prev_mouseX = data->player->mouse_x;
}

void	ft_key_press(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		check_for_door(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		data->is_shooting = true;
}

void	ft_mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_data	*data;

	data = param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		data->is_shooting = true;
}

void	ft_key_hold(void *param)
{
	t_data		*data;
	const char	*set = "159";

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		ft_exit(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, 0.05, 1, set);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -0.05, 1, set);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, 0.05, 0, set);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, -0.05, 0, set);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->angle -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->angle += 5;
}
