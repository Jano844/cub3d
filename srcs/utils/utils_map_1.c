/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/18 17:13:30 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_map_height(char *input)
{
	int		count;
	int		fd;
	char	*line;

	count = 0;
	fd = open(input, O_RDONLY);
	if (fd <= 0)
		return (ft_error("Error: failed to open input!"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	return (free(line), close(fd), count);
}

int	ft_map_len(char **tmp_map)
{
	int	count;

	count = 0;
	while (tmp_map[count])
		count++;
	return (count);
}

char	*ft_strtok(char *src, char delim, int x, int i)
{
	char	*result;
	int		max;

	max = ft_strlen(src) + 1;
	while (src && i < max)
	{
		if ((src && !src[i]) || src[i] == delim)
		{
			result = ft_calloc(i + 1, 1);
			if (!result)
				return (NULL);
			while (src && src[x] && x < i)
			{
				result[x] = src[x];
				x++;
			}
			if (result && result[0])
				return (result);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}
