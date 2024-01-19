/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:55:05 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/13 13:57:39 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_max_y(char **map)
{
	int	max_y;
	int	i;

	i = -1;
	max_y = 0;
	while (map[++i] != NULL)
		max_y++;
	return (max_y);
}

int	get_max_x(char **map)
{
	int	max;
	int	i;
	int	j;

	i = 0;
	max = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (j >= max)
				max = j;
			j++;
		}
		i++;
	}
	return (max);
}

void	initialize(int diff, int max_x_y[2], char **copied_map)
{
	if (diff == 0)
	{
		max_x_y[0] = get_max_x(copied_map);
		max_x_y[1] = get_max_y(copied_map);
	}
	else
	{
		max_x_y[0] += 4;
		max_x_y[1] += 4;
	}
}

char	**cpy_map(char **original, int size)
{
	char	**copy;
	int		i;

	copy = ft_calloc(size, sizeof(char *));
	if (!copy)
		return (NULL);
	i = -1;
	while (original[++i])
		copy[i] = ft_strdup(original[i]);
	return (copy);
}

bool	ft_valid_chars(t_data *data, int max_y)
{
	int		y;
	int		x;

	y = 0;
	while (data->game->map[y])
	{
		x = 0;
		while (data->game->map[y][x])
		{
			if (!ft_is_in_set(data->game->map[y][x], "150NESW "))
				return (true);
			x++;
		}
		y++;
	}
	data->game->map_dda = cpy_map(data->game->map, max_y + 1);
	return (false);
}
