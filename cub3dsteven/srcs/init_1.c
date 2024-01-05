/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2024/01/04 17:57:23 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	init_helper(t_data *data, char *input)
{
	if (init_map(data, input))
		return (1);
	if (data->game->width * SIZE < 1920)
		data->width = data->game->width * SIZE;
	else
		data->width = 1920;
	if (data->game->height * SIZE < 1080)
		data->height = data->game->height * SIZE;
	else
		data->height = 1080;
	return (0);
}

static void	init_minimap(t_data *data)
{
	data->minimap->width = data->game->width;
	data->minimap->height = -1;
	data->minimap->map = ft_calloc(data->game->height + 1, sizeof(int *));
	while (++data->minimap->height < data->game->height)
		data->minimap->map[data->minimap->height] = ft_calloc(data->game->height
				+ 1, sizeof(int));
}

int	init(t_data *data, char *input)
{
	if (init_helper(data, input))
		return (1);
	if (!(data->mlx = mlx_init(data->width, data->height, "cub3D", false)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	if (!(data->img->img_game = mlx_new_image(data->mlx, data->game->width
				* SIZE, data->game->height * SIZE)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	if (!(data->img->img_player_ray = mlx_new_image(data->mlx, data->game->width
				* 16, data->game->height * 16)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	if (init_img_one(data) || init_img_two(data))
		return (1);
	init_minimap(data);
	init_coords(data, 0, 0);
	init_player(data);
	draw_minimap(data);


	return (0);
}
