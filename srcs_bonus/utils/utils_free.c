/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/13 14:15:16 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free2d_until(void **str, int max_len)
{
	int	i;

	i = 0;
	while (str[i] != NULL && i < max_len)
		free(str[i++]);
	free(str);
}

void	ft_free2d_char(char **str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return ;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

void	ft_free2d_int(int **str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return ;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

void	ft_free_structs(t_data *data)
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

void	ft_exit(t_data *data, bool is_init)
{
	ft_check_free(data->game->no);
	ft_check_free(data->game->so);
	ft_check_free(data->game->ea);
	ft_check_free(data->game->we);
	ft_check_free(data->game->f);
	ft_check_free(data->game->c);
	ft_check_free_text(data->img->txt_no);
	ft_check_free_text(data->img->txt_so);
	ft_check_free_text(data->img->txt_ea);
	ft_check_free_text(data->img->txt_we);
	ft_check_free_text(data->img->txt_door_closed);
	if (data->game->is_random_map)
		ft_free2d_char(data->game->rnd_map);
	ft_free2d_char(data->game->tmp_map);
	ft_free2d_char(data->game->map);
	ft_free2d_char(data->game->map_dda);
	ft_free2d_int(data->minimap->map);
	if (!is_init)
		mlx_terminate(data->mlx);
	ft_free_structs(data);
}
