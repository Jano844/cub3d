/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/16 00:01:58 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_free2d(char **str)
{
	for (int i = 0; str[i] != NULL; i++)
	{
		free(str[i]);
	}
	free(str);
}

void	ft_exit(t_data *data)
{
	// ft_free2d(data->map->map);
	mlx_terminate(data->mlx);
	free(data->map);
	free(data);
	exit(0);
}
