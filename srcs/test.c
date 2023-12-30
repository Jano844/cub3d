/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/30 17:53:31 by jsanger          ###   ########.fr       */
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
	float	temp1 = -1;
	float	temp2 = -1;
	int		j = 0;
	int		angle;
	char	dir = 0;
	uint32_t color;

	angle = data->player->view_angle / 2;
	for (float k = data->player->view_angle / 2; k >= -data->player->view_angle / 2; k -= 1) // iterate throug all rays from - view_angle/2 bis view_angle /2
	{
		float height = calc_dist(data, k, &dir);
		for (float i = (data->image->width / data->player->view_angle) * j; i < (data->image->width / data->player->view_angle) * (j + 1); ++i)
		{
			float tmp = height * cos((angle) * PI / 180);
			float linehight = (data->image->height / 2) + (SIZE * 3 / tmp); // nach unten
			float linehight1 = (data->image->height / 2) - (SIZE * 3 / tmp); // nach oben
			if (linehight1 < 0)
				linehight1 = 0;
			if (linehight >= data->image->height)
				linehight = data->image->height;

			for (int32_t y = data->image->height / 2; y < linehight; y++)
			{
				if (dir == 'x')
					color = ft_pixel(0, 255, 255, 255);
				else
					color = ft_pixel(0, 255, 255, 150);
				mlx_put_pixel(data->image, i, y, color);
			}
			for (int32_t y = data->image->height / 2; y > linehight1; y--)
			{
				if (dir == 'x')
					color = ft_pixel(0, 255, 255, 255);
				else
					color = ft_pixel(0, 255, 255, 150);
				mlx_put_pixel(data->image, i, y, color);
			}
		}
		angle--;
		j++;
	}
	// mlx_image_to_window(data->mlx, data->image, 0, 0);
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
		data->player->x += 0.1 * cos(degrees_to_radians(data->player->angle));
		data->player->y += 0.1 * sin(degrees_to_radians(data->player->angle));
		reset(data);
		calc_view(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player->x += 0.1 * cos(degrees_to_radians(data->player->angle + 180));
		data->player->y += 0.1 * sin(degrees_to_radians(data->player->angle + 180));
		reset(data);
		calc_view(data);
	}
		if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player->x += 0.1 * cos(degrees_to_radians(data->player->angle + 270));
		data->player->y += 0.1 * sin(degrees_to_radians(data->player->angle + 270));
		reset(data);
		calc_view(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player->x += 0.1 * cos(degrees_to_radians(data->player->angle + 90));
		data->player->y += 0.1 * sin(degrees_to_radians(data->player->angle + 90));
		reset(data);
		calc_view(data);
	}


	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player->angle += 5;
		if (data->player->angle >= 360)
			data->player->angle -= 360;
		reset(data);
		calc_view(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player->angle -= 5;
		if (data->player->angle <= 0)
			data->player->angle += 360;
		reset(data);
		calc_view(data);
	}
	usleep(10000);
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
	data->player->angle = 0;
	data->player->x = 0;
	data->player->y = 0;
	data->player->view_angle = 80;
}

int	init(t_data *data, t_map *map, t_player *player,char *input)
{
	get_map(map, input);
	map->width -= 1;
	int	temp_height = 128 * 10;
	int	temp_width = 128 * 7;
	if (!(data->mlx = mlx_init(temp_height, temp_width, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (!(data->image = mlx_new_image(data->mlx, temp_height, temp_width)))
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
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_loop(data->mlx);
	ft_exit(data);
	// char	dir = 0;
	// // for (float	i = 45; i < 135; i += 1)
	// // {
	// // 	float dist = calc_dist(data, i, &dir);
	// // 	// if (dist < 1 && !(i < 45 || i > 225))
	// // 	// 	printf("in test: %.2f %.1f  %c\n", dist, i, dir);
	// // }
	// calc_dist(data, 134, &dir);
}
