/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/18 17:55:43 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void reset(t_data *data)
{
	for (int32_t i = 0; i < data->image->width; ++i)
	{
		for (int32_t y = 0; y < data->image->height; ++y)
		{
			uint32_t color = ft_pixel(0, 0, 0, 255);
			mlx_put_pixel(data->image, i, y, color);
		}
	}
}

void	calc_view(t_data *data)
{
	float	temp1;
	float	temp2;
	int		j = 0;
	int		angle;

	temp1 = data->player->view_angle / 2;
	temp2 = -temp1;


	angle = temp1;
	for (float k = temp2; k <= temp1; k += 01)
	{
		float height = ray_distance(data, k);
		for (float i = (data->image->width / data->player->view_angle) * j; i < (data->image->width / data->player->view_angle) * (j + 1); ++i)
		{
			float tmp = height * cos((angle) * PI / 180);
			float linehight = (data->image->height / 2) + (SIZE * 3 / tmp);
			float linehight1 = (data->image->height / 2) - (SIZE * 3 / tmp);
			if (linehight1 < 0)
				linehight1 = 0;
			if (linehight >= data->image->height)
				linehight = data->image->height;

			for (int32_t y = data->image->height / 2; y < linehight; y++)
			{
				uint32_t color = ft_pixel(0, 255, 255, 255);
				mlx_put_pixel(data->image, i, y, color);
			}
			for (int32_t y = data->image->height / 2; y > linehight1; y--)
			{
				uint32_t color = ft_pixel(0, 255, 255, 255);
				mlx_put_pixel(data->image, i, y, color);
			}
		}
		angle--;
		j++;
	}
	mlx_image_to_window(data->mlx, data->image, data->map->height, data->map->width);
		// printf("%0.3f\n", ray_distance(data, i));
		// for (float i = (data->image->width / data->player->view_angle) * j; i < (data->image->width / data->player->view_angle) * (j + 1); ++i)
}

void ft_hook(void* param)
{
	t_data *data = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(data->mlx, data->image);
		ft_exit(data);
	}

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player->y += 0.08;
		reset(data);
		calc_view(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player->y -= 0.08;
		reset(data);
		calc_view(data);
	}
		if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player->x += 0.08;
		reset(data);
		calc_view(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player->x -= 0.08;
		reset(data);
		calc_view(data);
	}


	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player->angle += 5;
		reset(data);
		calc_view(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player->angle -= 5;
		reset(data);
		calc_view(data);
	}
}

void	get_player_coords(t_data *data)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = 0;
	pixel_y = 0;
	for (int i = 0; data->map->map[i] != NULL; i++)
	{
		for (int j = 0; data->map->map[i][j] != '\0'; j++)
		{
			if (data->map->map[i][j] == 'P')
			{
				data->player->x = pixel_x + 0.5;
				data->player->y = pixel_y + 0.5;
				return ;
			}
			pixel_x += 1;
		}
		pixel_x = 0;
		pixel_y += 1;
	}
}

void	struct_declaration(t_data *data)
{
	data->player->angle = 90;
	data->player->x = 0;
	data->player->y = 0;
	data->player->view_angle = 80;
}

int	init(t_data *data, t_map *map, t_player *player,char *input)
{
	get_map(map, input);
	map->width -= 1;
	if (!(data->mlx = mlx_init(map->width * SIZE, map->height * SIZE, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (!(data->image = mlx_new_image(data->mlx, map->height * SIZE, map->width * SIZE)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		exit(1);
	}
	data->player = player;
	data->map = map;
	struct_declaration(data);
	get_player_coords(data);
	reset(data);
	calc_view(data);
	return (0);
}

int main(int argc, char** argv)
{
	t_map		*map;
	t_player	*player;
	t_data		*data;

	data = malloc(sizeof(t_data));
	map = malloc(sizeof(t_map));
	player = malloc(sizeof(t_player));

	if (init(data, map, player, argv[1]))
		return (1);

	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	ft_exit(data);
}
