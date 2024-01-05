/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/04 16:08:06 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free2d_char(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

void	ft_free2d_int(int **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

void	free_structs(t_data *data)
{
	if (data->player != NULL)
		free(data->player);
	if (data->minimap != NULL)
		free(data->minimap);
	if (data->game != NULL)
		free(data->game);
	if (data->img != NULL)
		free(data->img);
	if (data != NULL)
		free(data);
}

void	ft_exit(t_data *data)
{
	free(data->img->col_NO);
	free(data->img->col_SO);
	free(data->img->col_WE);
	free(data->img->col_EA);
	ft_free2d_char(data->game->map);
	ft_free2d_char(data->game->tmp_map);
	ft_free2d_int(data->minimap->map);
	mlx_terminate(data->mlx);
	free_structs(data);
	exit(0);
}
