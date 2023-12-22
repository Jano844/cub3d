/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:13:52 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/19 00:39:28 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float berechneSchnittpunkt(float m, float c)
{
	if (m == 0)
	{
		printf("Die Geraden sind parallel und schneiden sich für jedes x.\n");
		return 0; // Rückgabe des beliebigen x-Werts
	}
	float schnittpunkt = -c / m;

	return schnittpunkt;
}

void	draw_triangle(t_data *data, float a, float h, int x, int y, int dir)
{
	float m = h / a;
	float	c = y;

	float j;
	int	verschiebung = -1;
	if (dir == 1)
		x = x - a;
	for (int i = 0; i < h; i++)
		verschiebung++;
	for (int i = 0; i < h; i++)
	{
		float collision = i / m;
		if (dir == 1)
			collision = a - collision;
		j = 0;
		if (dir == 0)
		{
			while (j < collision)
			{
				uint32_t color = ft_pixel(0, 255, 255, 255);
				if (i + y - verschiebung > 0)
					mlx_put_pixel(data->image, j + x, i + y - verschiebung, color);
				j++;
			}
		}
		if (dir == 1)
		{
			while (j + collision < a)
			{
				uint32_t color = ft_pixel(0, 255, 255, 255);
				if (i + y > 0)
					mlx_put_pixel(data->image, j + collision + x, i + y, color);
				j++;
			}
		}
	}
}
	// f(x) = mx + c;


#include <stdio.h>

// Funktion zur Berechnung des Schnittpunkts von f(x) = c und f(x) = mx + c

// int main() {
// 	// Beispielwerte für c und m
// 	float c1 = 1.0;
// 	float m2 = 2.0;
// 	float c2 = 5.0;

// 	// Berechnung des Schnittpunkts
// 	float schnittpunkt = berechneSchnittpunkt(m2, c1);

// 	// Ausgabe des Ergebnisses
// 	printf("Die Geraden schneiden sich bei x = %.2f\n", schnittpunkt);

// 	return 0;
// }
