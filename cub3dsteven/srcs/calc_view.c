/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:25 by slippert          #+#    #+#             */
/*   Updated: 2024/01/05 03:38:54 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Funktion: calc_preset
// Zweck: Initialisiert die notwendigen Werte für die Berechnung der Sichtlinien.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - calc: Zeiger auf die Struktur,
//		die Informationen für die Berechnungen enthält.
//
// Die Funktion setzt verschiedene Werte wie Winkel, Farben und Zählvariablen
// für die Berechnungen der Sichtlinien. Zudem wird der bestehende Bildspeicher
// gelöscht und ein neuer Bildspeicher für die Sichtlinien erstellt.
void	calc_preset(t_data *data, t_calc_view *calc)
{
	calc->j = 0;
	calc->max_lines = -(data->player->view_angle / 2);
	calc->temp2 = -calc->max_lines;
	calc->angle = -calc->max_lines;
	calc->color_wall = ft_pixel(56, 76, 200, 255);
	calc->color_door = ft_pixel(125, 76, 56, 255);
	calc->color_portal = ft_pixel(56, 125, 125, 255);
	calc->line = calc->max_lines * -1;
	calc->treshold = (float)6.2f * (data->width / 1920.0);
	calc->direction = '\0';
}

void	reset_map(t_data *data)
{
	for (int y = 0; data->game->map[y] != NULL; y++)
	{
		for (int x = 0; data->game->map[y][x] != '\0'; x++)
		{
			if (data->game->map[y][x] == 'L')
				data->game->map[y][x] = '1';
		}
	}
}

void	get_calc_color(t_calc_view *calc)
{
	if (calc->direction == 'N')
		calc->color_wall = ft_pixel(227, 66, 245, 255);
	else if (calc->direction == 'E')
		calc->color_wall = ft_pixel(245, 158, 66, 255);
	else if (calc->direction == 'S')
		calc->color_wall = ft_pixel(66, 135, 245, 255);
	else if (calc->direction == 'W')
		calc->color_wall = ft_pixel(66, 245, 120, 255);
}

void	calc_block_width(t_data *data, t_calc_view *calc, bool new_block, float quality)
{
	float	temp_calc_line = calc->line;
	float	temp_calc_maxline = calc->max_lines;
	float	temp_calc_angle = calc->angle;
	float	temp_calc_t = 0;
	float	dist;
	int		i = 0;

	while (temp_calc_line > temp_calc_maxline)
	{
		data->wall_type = 'W';
		dist = calc_dist(data, temp_calc_line, &calc->direction, &new_block);
		if (new_block == true)
		{
			calc->width_array[i] = temp_calc_t;
			i++;
		}
		temp_calc_angle -= 1 / (float)quality;
		temp_calc_t++;
		temp_calc_line -= 1 / (float)quality;
	}
	if (new_block == true)
		calc->width_array[i] = FLT_MAX;
	else
	{
		while (new_block == false)
		{
			data->wall_type = 'W';
			dist = calc_dist(data, temp_calc_line, &calc->direction, &new_block);
			temp_calc_angle -= 1 / (float)quality;
			temp_calc_t++;
			temp_calc_line -= 1 / (float)quality;
		}
	}
	if (new_block == true)
		calc->width_array[i] = FLT_MAX;
	calc->width_array[i] = temp_calc_t;
		i++;
	calc->width_array[i] = FLT_MAX;
}

// Funktion: calc_view
// Zweck: Berechnet und zeichnet die Sichtlinien im Spiel.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//
// Die Funktion initialisiert die notwendigen Werte, iteriert über die
// Sichtlinien und ruft die Hilfsfunktion calc_helper für jede Sichtlinie auf.
// Das Ergebnis wird im Fenster angezeigt.
void	calc_view(t_data *data)
{
	t_calc_view	calc;
	float	quality;
	float	block_width;
	bool	new_block;

	calc_preset(data, &calc);
	quality = data->img->img_game->width; // Need to use the width of the screen
	quality = 1 / (fabs(calc.max_lines) / (quality / 2)) / QUALITY;
	new_block = false;
	reset_map(data);
	calc_block_width(data, &calc, new_block, quality);
	calc.direction = '\0';
	new_block = false;
	reset_map(data);
	while (calc.line > calc.max_lines)
	{
		data->wall_type = 'W';
		calc.distance = calc_dist(data, calc.line, &calc.direction, &new_block);
		get_calc_color(&calc);
		if (new_block == false)
		{
			draw_texture(data, &calc, new_block);
		}
		else
		{
			calc.color_wall = ft_pixel(0, 0, 0, 255);
			draw_texture(data, &calc, new_block);
		}
		calc.angle -= 1 / (float)quality;
		calc.j++;
		calc.line -= 1 / (float)quality;
	}
	usleep(1000 * 10);
}
