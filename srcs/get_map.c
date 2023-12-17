/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/15 21:26:34 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_map_hight(t_map *map, char *input)
{
	int	count;
	int	fd;
	char	*line;

	count = 0;
	fd = open(input, O_RDONLY);
	line = get_next_line(fd);
	map->width = (int)ft_strlen(line);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	free(line);
	close(fd);
	return (count);
}

void	get_map(t_map *map, char *input)
{
	int	count;
	int	fd;
	char	*line;

	count = 0;
	fd = open(input, O_RDONLY);
	map->height = get_map_hight(map, input);
	map->map = ft_calloc(sizeof(char *), map->height);
	while (count < map->height)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			map->map[count] = line;
			count++;
		}
		else
			map->map[count] = NULL;
	}
	close(fd);
}
