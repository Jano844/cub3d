/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/18 17:15:20 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_count_comma(char *str)
{
	int	i;
	int	count_comma;

	i = 0;
	count_comma = 0;
	while (str[i])
	{
		if (str[i++] == ',')
			count_comma++;
	}
	return (count_comma);
}

int	ft_toktrim(char *rgb_str, char **r, char **g, char **b)
{
	int		offset;

	offset = 0;
	*r = ft_strtok(rgb_str, ',', 0, 0);
	if (*r == NULL)
		return (0);
	offset += ft_strlen(*r) + 1;
	*r = ft_strtrim_free(*r, " \t\n\v\f\r");
	*g = ft_strtok(rgb_str + (offset), ',', 0, 0);
	if (*g == NULL)
		return (0);
	offset += ft_strlen(*g) + 1;
	*g = ft_strtrim_free(*g, " \t\n\v\f\r");
	*b = ft_strtok(rgb_str + (offset), ',', 0, 0);
	if (*b == NULL)
		return (0);
	*b = ft_strtrim_free(*b, " \t\n\v\f\r");
	return (1);
}

int	ft_str_to_rgb(char *rgb_str, int *color)
{
	t_rgba	rgb;
	char	*r;
	char	*g;
	char	*b;

	if (ft_strlen(rgb_str) == 0 || ft_count_comma(rgb_str) != 2)
		return (0);
	if (ft_toktrim(rgb_str, &r, &g, &b) == 0)
		return (0);
	rgb.r = ft_atoi(r);
	rgb.g = ft_atoi(g);
	rgb.b = ft_atoi(b);
	if (rgb.r > 255 || rgb.g > 255 || rgb.b > 255 || rgb.r < 0 || rgb.g < 0
		|| rgb.b < 0)
		return (free(r), free(g), free(b), 0);
	*color = ft_pixel(rgb.r, rgb.g, rgb.b, 255);
	return (free(r), free(g), free(b), 1);
}
