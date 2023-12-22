/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/18 21:04:37 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double radians_to_degrees(double radians)
{
	return ((radians * 180) / PI);
}

double degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

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
