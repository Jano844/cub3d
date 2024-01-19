/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/18 16:50:26 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_fill_tmp(char **tmp_map, int fd)
{
	char	*line;
	int		y;
	int		extra;

	y = -1;
	extra = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		tmp_map[++y] = ft_calloc(ft_strlen(line) + 1, 1);
		if (!tmp_map[y])
			return (ft_free2d_until((void *)tmp_map, y),
				ft_error("Error: tmp_map[y] allocation failed!"));
		ft_strlcpy(tmp_map[y], line, ft_strlen_until(line, '\n') + 1);
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), 0);
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
		if (ft_strnstr(tmp_map[y], needle, ft_strlen(tmp_map[y])) != NULL)
			*texture = ft_strdup(ft_strnstr(tmp_map[y], needle,
						ft_strlen(tmp_map[y])));
		y++;
	}
	if (!*texture)
		return (0);
	*texture = ft_strtrim_free(*texture, needle);
	if (*texture == NULL)
		return (0);
	*texture = ft_strtrim_free(*texture, " \t\n\v\f\r");
	return (1);
}

static bool	ft_check_validation(t_data *data, int max_y)
{
	if (data->game->height > 20 || data->game->width > 64)
		return (ft_error("Error: height '20' or width '64' exceeded!"));
	if (ft_valid_chars(data, max_y))
		return (ft_error("Error: Map contains invalid characters!"));
	if (ft_valid_map(cpy_map(data->game->map, max_y + 1)))
		return (ft_error("Error: Map is not surrounded by walls!"));
	return (0);
}

static int	ft_fill_map(t_data *data, char **tmp_map)
{
	int	y_game;
	int	max_y;
	int	x;

	max_y = ft_map_len(tmp_map);
	y_game = 0;
	data->game->map = ft_calloc(max_y + 1, sizeof(char *));
	if (!data->game->map)
		return (ft_error("Error: data->game->map allocation failed!"));
	while (tmp_map && tmp_map[y_game + 6])
	{
		x = -1;
		data->game->map[y_game] = ft_calloc(ft_strlen(tmp_map[y_game + 6]) + 1,
				1);
		if (!data->game->map[y_game])
			return (ft_error("Error: data->game->map[y_game] alloc failed!"));
		while (tmp_map[y_game + 6][++x])
			data->game->map[y_game][x] = tmp_map[y_game + 6][x];
		if (data->game->width < ft_strlen(data->game->map[y_game]))
			data->game->width = ft_strlen(data->game->map[y_game]);
		y_game++;
	}
	data->game->height = y_game;
	return (ft_check_validation(data, max_y));
}

int	init_map(t_data *data, char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd <= 0)
		return (ft_error("Error: failed to open input!"));
	data->game->tmp_map = ft_calloc(get_map_height(input) + 1, sizeof(char *));
	if (!data->game->tmp_map)
		return (close(fd), ft_error("Error: tmp_map allocation failed!"));
	ft_fill_tmp(data->game->tmp_map, fd);
	if (!data->game->tmp_map)
		return (close(fd), 1);
	if (ft_get_text(data->game->tmp_map, &data->game->no, "NO")
		* ft_get_text(data->game->tmp_map, &data->game->so, "SO")
		* ft_get_text(data->game->tmp_map, &data->game->we, "WE")
		* ft_get_text(data->game->tmp_map, &data->game->ea, "EA")
		* ft_get_text(data->game->tmp_map, &data->game->f, "F")
		* ft_get_text(data->game->tmp_map, &data->game->c, "C") == 0)
		return (close(fd), ft_error("Error: Texture parsing!"));
	if (ft_str_to_rgb(data->game->f, &data->game->col_floor)
		* ft_str_to_rgb(data->game->c, &data->game->col_ceiling) == 0)
		return (close(fd), ft_error("Error: Color parsing!"));
	if (ft_fill_map(data, data->game->tmp_map))
		return (close(fd), 1);
	return (close(fd), 0);
}
// if (ft_fill_map(data, data->game->tmp_map) || ft_check_game_map(data))
// return (close(fd), 1);
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
