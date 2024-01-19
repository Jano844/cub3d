/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_door_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2024/01/12 12:05:46 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_wall_ray_helper(t_data *data, t_draw_rays *ray)
{
	int	ray_len;

	ray_len = 0;
	while (ray_len < 10)
	{
		set_coords(data, ray, ray_len);
		if (ray->x_coord >= 0 && ray->y_coord >= 0 && \
			(const uint32_t)ray->x_coord < data->img->img_movement_ray->width
			&& \
			(const uint32_t)ray->y_coord < data->img->img_movement_ray->height)
		{
			if (ft_is_in_set(data->game->map[ray->y_coord / 16][ray->x_coord
					/ 16], "1"))
				return (1);
			mlx_put_pixel(data->img->img_movement_ray, ray->x_coord,
				ray->y_coord, ray->color);
		}
		ray_len++;
	}
	return (0);
}

int	check_wall_ray(t_data *data)
{
	t_draw_rays	ray;
	int			breite;
	int			max;

	breite = 60;
	ray.color = ft_pixel(255, 0, 0, 125);
	ray.i = -breite / 2;
	max = ray.i + 20;
	while (ray.i <= breite / 2)
	{
		ray.angle_offset = ray.i;
		if (check_wall_ray_helper(data, &ray))
			return (1);
		ray.i += 0.1f;
	}
	return (0);
}

static int	check_for_door_preset(t_data *data, t_check_door *door)
{
	door->radian_angle = data->player->angle * PI / 180.0;
	door->p_x_cos = cos(door->radian_angle);
	door->p_y_sin = sin(door->radian_angle);
	door->cell_y = roundf(data->player->y - 1 * door->p_y_sin);
	door->cell_x = roundf(data->player->x + 1 * door->p_x_cos);
	if (door->cell_y >= 0 && door->cell_y <= data->game->height
		&& door->cell_x >= 0 && door->cell_x <= data->game->width)
	{
		door->instance = \
		data->minimap->map[(int)door->cell_y][(int)door->cell_x];
		return (door->instance);
	}
	return (-1);
}

void	check_for_door(t_data *data)
{
	t_check_door	door;

	if (check_for_door_preset(data, &door) == -1)
		return ;
	if (data->game->map[(int)door.cell_y][(int)door.cell_x] == '9')
	{
		data->player->x = data->game->width / 2;
		data->player->y = data->game->height / 2;
		data->img->img_player->instances[0].x = data->player->x * 16;
		data->img->img_player->instances[0].y = data->player->y * 16;
	}
	if (data->game->map[(int)door.cell_y][(int)door.cell_x] == '5')
	{
		data->game->map[(int)door.cell_y][(int)door.cell_x] = '4';
		data->img->img_mm_door_closed->instances[door.instance].enabled = 0;
	}
	else if (data->game->map[(int)door.cell_y][(int)door.cell_x] == '4')
	{
		data->game->map[(int)door.cell_y][(int)door.cell_x] = '5';
		data->img->img_mm_door_closed->instances[door.instance].enabled = 1;
	}
}
