/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:23:47 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/12 11:38:53 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_path_check(char **map, int x, int y, int max_x_y[2])
{
	if (x <= 0 || x >= max_x_y[0] || y <= 0 || y >= max_x_y[1])
		return ;
	map[y][x] = 'F';
	if (map[y + 1][x] == '0')
		ft_path_check(map, x, y + 1, max_x_y);
	if (map[y][x + 1] == '0')
		ft_path_check(map, x + 1, y, max_x_y);
	if (map[y - 1][x] == '0')
		ft_path_check(map, x, y - 1, max_x_y);
	if (map[y][x - 1] == '0')
		ft_path_check(map, x - 1, y, max_x_y);
}

char	**allocate_big_map_0(int y, int x)
{
	char	**map;
	int		i;
	int		j;

	map = malloc((y + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < y)
	{
		j = 0;
		map[i] = malloc((x + 1) * sizeof(char));
		if (!map[i])
			return (NULL);
		while (j < x)
		{
			map[i][j] = '0';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	**process_map(char **copied_map, int max_x, int max_y)
{
	char	**processed_map;
	int		j;
	int		i;

	i = 0;
	processed_map = allocate_big_map_0(max_y + 5, max_x + 5);
	while (copied_map[i] != NULL)
	{
		j = 0;
		while (copied_map[i][j] != '\0')
		{
			if (copied_map[i][j] == '1')
				processed_map[i + 2][j + 2] = '1';
			if (copied_map[i][j] == 'N' || copied_map[i][j] == 'E'
				|| copied_map[i][j] == 'S' || copied_map[i][j] == 'W')
				processed_map[i + 2][j + 2] = 'P';
			j++;
		}
		i++;
	}
	return (processed_map);
}

void	helper(char **processed_map, char **copied_map, bool *test)
{
	if (processed_map[1][1] == 'F')
		*test = true;
	else
		*test = false;
	ft_free2d_char(copied_map);
	ft_free2d_char(processed_map);
}

bool	ft_valid_map(char **copied_map)
{
	bool	test;
	int		max_x_y[2];
	int		i;
	int		j;
	char	**processed_map;

	initialize(0, max_x_y, copied_map);
	processed_map = process_map(copied_map, max_x_y[0], max_x_y[1]);
	initialize(1, max_x_y, copied_map);
	i = 0;
	while (processed_map[i] != NULL)
	{
		j = -1;
		while (processed_map[i][++j] != '\0')
		{
			if (processed_map[i][j] == 'P')
			{
				ft_path_check(processed_map, j, i, max_x_y);
				break ;
			}
		}
		i++;
	}
	helper(processed_map, copied_map, &test);
	return (test);
}
