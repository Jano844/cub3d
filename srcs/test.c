/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/17 22:27:27 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(t_data *data)
{
	for (int32_t i = 0; i < data->image->width; ++i)
	{
		for (int32_t y = 0; y < data->image->height; ++y)
		{
			uint32_t color = ft_pixel(0, 255, 255, 255);
			mlx_put_pixel(data->image, i, y, color);
		}
	}
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
		data->image->instances[0].y -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->image->instances[0].y += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->image->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->image->instances[0].x += 5;
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
	// data->player->angle = 25;
	data->player->x = 0;
	data->player->y = 0;
}

int	init(t_data *data, t_map *map, t_player *player,char *input)
{
	get_map(map, input);
	if (!(data->mlx = mlx_init(map->width * 64, map->height * 64, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (!(data->image = mlx_new_image(data->mlx, map->height, map->width)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	data->player = player;
	data->map = map;
	data->map->width -= 1;
	struct_declaration(data);
	get_player_coords(data);
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
	data->player->angle = ft_atoi(argv[2]);
	// ft_randomize(data);
	// mlx_image_to_window(data->mlx, data->image, 100, 100);

	// mlx_loop_hook(data->mlx, ft_hook, data);
	// mlx_loop(data->mlx);
	printf("distance to wall: %0.5f\n", test(data));
	ft_exit(data);
}
