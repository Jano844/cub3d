/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/04 11:34:00 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	**ft_fill_tmp(char **tmp_map, int fd)
{
	char	*line;
	int		y;
	int		x;

	y = -1;
	line = get_next_line(fd);
	while (line)
	{
		x = 0;
		if (line && line[x] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		tmp_map[++y] = ft_calloc(ft_strlen(line) + 1, 1);
		if (!tmp_map[y])
			return (ft_error("Error: tmp_map[y] allocation failed!"), NULL);
		x = -1;
		while (line[++x] && line[x] != '\n')
			tmp_map[y][x] = line[x];
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), tmp_map);
}

static int	ft_get_text(char **tmp_map, char *(*texture), char *needle)
{
	int	y;
	int	max_y;

	max_y = 0;
	while (tmp_map[max_y])
		max_y++;
	y = 0;
	*texture = NULL;
	while (!*texture && y < max_y)
	{
		*texture = ft_strnstr(tmp_map[y], needle, ft_strlen(tmp_map[y]));
		y++;
	}
	if (!*texture)
		return (0);
	*texture = ft_strtrim_free(*texture, needle);
	*texture = ft_strtrim_free(*texture, " \t\n\v\f\r");
	return (1);
}

static int	ft_fill_map(t_data *data, char **tmp_map)
{
	int		y_game;
	int		max_y;
	int		x;

	max_y = ft_map_len(tmp_map);
	y_game = 0;
	data->game->map = ft_calloc(max_y + 1, sizeof(char *));
	if (!data->game->map)
		return (ft_error("Error: data->game->map allocation failed!"));
	while (tmp_map && tmp_map[y_game + 6])
	{
		x = -1;
		data->game->map[y_game] = ft_calloc(ft_strlen(tmp_map[y_game + 6]) + 1, 1);
		if (!data->game->map[y_game])
			return (ft_error("Error: data->game->map[y_game] allocation failed!"));
		while (tmp_map[y_game + 6][++x])
			data->game->map[y_game][x] = tmp_map[y_game + 6][x];
		if (data->game->width < ft_strlen(data->game->map[y_game]))
			data->game->width = ft_strlen(data->game->map[y_game]);
		y_game++;
	}
	data->game->height = y_game;
	return (0);
}

int	init_map(t_data *data, char *input)
{
	int		fd;

	fd = open(input, O_RDONLY);
	if (!fd)
		return (ft_error("Error: failed to open input!"));
	data->game->tmp_map = ft_calloc(get_map_height(input) + 1, sizeof(char *));
	if (!data->game->tmp_map)
		return (close(fd), ft_error("Error: tmp_map allocation failed!"));
	data->game->tmp_map = ft_fill_tmp(data->game->tmp_map, fd);
	if (!data->game->tmp_map)
		return (1);
	if (ft_get_text(data->game->tmp_map, &data->game->NO, "NO")
		* ft_get_text(data->game->tmp_map, &data->game->SO, "SO")
		* ft_get_text(data->game->tmp_map, &data->game->WE, "WE")
		* ft_get_text(data->game->tmp_map, &data->game->EA, "EA")
		* ft_get_text(data->game->tmp_map, &data->game->F, "F")
		* ft_get_text(data->game->tmp_map, &data->game->C, "C") == 0)
		return (ft_error("Error: Texture parsing!"));
	if (ft_str_to_rgb(data->game->F, &data->game->color_floor)
		* ft_str_to_rgb(data->game->C, &data->game->color_ceiling) == 0)
		return (ft_error("Error: Color parsing!"));
	if (ft_fill_map(data, data->game->tmp_map))
		return (1);
	return (close(fd), 0);
}
// for (int i = 0; tmp_map[i]; i++)
// 	printf("%s\n", tmp_map[i]);
// printf("\n");
// printf("%s\n", data->game->NO);
// printf("%s\n", data->game->SO);
// printf("%s\n", data->game->WE);
// printf("%s\n", data->game->EA);
// printf("%s\n", data->game->F);
// printf("%s\n", data->game->C);
// printf("\n");
// for (int i = 0; data->game->map[i]; i++)
// 	printf("%s\n", data->game->map[i]);
