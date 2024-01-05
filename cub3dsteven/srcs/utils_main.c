/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/04 17:54:02 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_img_to_window(t_data *data)
{
	int	width;
	int	height;
	int	i;

	i = 0;
	width = data->width / 2 - data->img->img_pistol[0]->width / 2;
	height = data->height - data->img->img_pistol[0]->height;
	mlx_image_to_window(data->mlx, data->img->img_player_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->img->img_pistol[0], width, height);
	mlx_image_to_window(data->mlx, data->img->img_pistol[1], width, height);
	mlx_image_to_window(data->mlx, data->img->img_pistol[2], width, height);
	mlx_image_to_window(data->mlx, data->img->img_pistol[3], width, height);
	mlx_image_to_window(data->mlx, data->img->img_pistol[4], width, height);
	while (i < 4)
	{
		data->img->img_pistol[i++]->enabled = false;
	}
	data->img->pistol_frame = 0;
	mlx_image_to_window(data->mlx, data->img->img_game, 0, 0);
	data->img->img_game->instances[0].z = 0;
}

void	reset_window(t_data *data)
{
	ft_memset(data->img->img_game->pixels, 0, data->img->img_game->width
		* data->img->img_game->height * sizeof(int32_t));
}

void	ft_running(void *param)
{
	t_data	*data;

	data = param;
	reset_window(data);
	calc_view(data);
	draw_player_rays(data, 80);
}

int	ft_check_extension(char *argv)
{
	int			len;
	int			i;
	const char	*extension = ".cub";

	len = ft_strlen(argv) - 4;
	i = 0;
	while (extension[i])
	{
		if (!argv[len] || extension[i] != argv[len])
			return (ft_error("Error: Map extension incorrect. Expected: (.cub)"));
		len++;
		i++;
	}
	return (0);
}
