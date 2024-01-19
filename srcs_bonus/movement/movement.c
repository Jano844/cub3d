/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2024/01/17 19:50:16 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	move_player_preset(t_data *data, float *speed, float *dst)
{
	if (*speed > 0)
	{
		*dst = 0.5f;
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
			*speed += 0.15f;
	}
	else
	{
		*dst = -0.5f;
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
			*speed -= 0.15f;
	}
}

void	move_player(t_data *data, float speed, int forward)
{
	float	radian_angle;
	float	p_x_cos;
	float	p_y_sin;
	float	dst;

	move_player_preset(data, &speed, &dst);
	if (forward == 1)
		radian_angle = data->player->angle * PI / 180.0;
	else
		radian_angle = (data->player->angle + 90.0) * PI / 180.0;
	if (check_wall_ray(data))
		return ;
	p_x_cos = speed * cos(radian_angle);
	p_y_sin = speed * sin(radian_angle);
	data->player->x += p_x_cos;
	data->player->y -= p_y_sin;
	data->img->img_player->instances[0].x = data->player->x * 16;
	data->img->img_player->instances[0].y = data->player->y * 16;
}
