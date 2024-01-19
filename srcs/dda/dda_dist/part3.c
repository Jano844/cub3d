/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/12 00:26:05 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// second condition block
void	first_if_conition(t_vec2 *vec, char *dir, bool *xminus, bool *yminus)
{
	if (vec->angle >= 90 && vec->angle <= 270)
	{
		*xminus = true;
		vec->x -= vec->distx / 10;
		*dir = 'W';
	}
	else
	{
		vec->x += vec->distx / 10;
		*dir = 'E';
	}
	if (vec->angle >= 0 && vec->angle <= 180)
	{
		*yminus = true;
		vec->y -= sqrt(pow(vec->tempx, 2) - pow((vec->distx / 10), 2));
	}
	else
		vec->y += sqrt(pow(vec->tempx, 2) - pow((vec->distx / 10), 2));
}

void	second_if_conition(t_vec2 *vec, char *dir, bool *xminus, bool *yminus)
{
	if (vec->angle >= 0 && vec->angle <= 180)
	{
		*yminus = true;
		vec->y -= vec->disty / 10;
		*dir = 'N';
	}
	else
	{
		vec->y += vec->disty / 10;
		*dir = 'S';
	}
	if (vec->angle >= 90 && vec->angle <= 270)
	{
		*xminus = true;
		vec->x -= sqrt(pow(vec->tempy, 2) - pow((vec->disty / 10), 2));
	}
	else
		vec->x += sqrt(pow(vec->tempy, 2) - pow((vec->disty / 10), 2));
}
// first condition block

void	first_conition(t_vec2 *vec, bool *xminus)
{
	if (vec->angle >= 90 && vec->angle <= 270)
	{
		*xminus = true;
		vec->x -= vec->distx / 10;
	}
	else
		vec->x += vec->distx / 10;
}

void	second_conition(t_vec2 *vec, bool *yminus)
{
	if (vec->angle >= 0 && vec->angle <= 180)
	{
		*yminus = true;
		vec->y -= vec->disty / 10;
	}
	else
		vec->y += vec->disty / 10;
}

float	start_dist(t_vec2 *vec, char *dir, bool *xminus, bool *yminus)
{
	init_dist_x_y(vec);
	if (vec->angle == 0 || vec->angle == 180)
	{
		first_conition(vec, xminus);
		return (vec->distx / 10);
	}
	if (vec->angle == 90 || vec->angle == 270)
	{
		second_conition(vec, yminus);
		return (vec->disty / 10);
	}
	vec->tempx = (vec->distx * sqrt(1 + pow(vec->m, 2))) / 10;
	vec->tempy = (vec->disty * sqrt(1 + pow(1 / vec->m, 2))) / 10;
	if (vec->m == 0)
		return (vec->tempx);
	if (vec->tempx < vec->tempy)
	{
		first_if_conition(vec, dir, xminus, yminus);
		return (vec->tempx);
	}
	second_if_conition(vec, dir, xminus, yminus);
	return (vec->tempy);
}
