/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/17 19:48:58 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	return (1);
}

int	ft_is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen_until(char *str, int c)
{
	int				count;
	unsigned char	u_c;

	u_c = (unsigned char)c;
	count = 0;
	while (str[count])
	{
		if (str[count] == u_c)
			break ;
		count++;
	}
	return (count);
}

void	ft_change_item(t_data *data)
{
	int	i;

	i = 0;
	data->player->curr_item = ++data->player->curr_item % 2;
	while (data->player->curr_item == 1 && i < 5)
		data->img->img_pistol[i++]->enabled = false;
	while (data->player->curr_item == 0 && i < 6)
		data->img->img_torch[i++]->enabled = false;
	if (data->player->curr_item == 1)
		data->is_torching = true;
	else
		data->is_torching = false;
	i = 0;
	while (data->player->curr_item == 0 && i < 5)
	{
		if (4 == i)
			data->img->img_pistol[i++]->enabled = true;
		else
			data->img->img_pistol[i++]->enabled = false;
	}
}

void	reset_window(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while ((const uint32_t)y < data->img->img_game->height)
	{
		x = 0;
		while ((const uint32_t)x < data->img->img_game->width)
		{
			ft_pixel(0, 0, 0, 0);
			x++;
		}
		y++;
	}
}
