/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 00:19:56 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/12 00:26:19 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	inital(t_dda *dda, t_dda_helper *dda_tmp, float quality)
{
	dda_tmp->line = dda->line;
	dda_tmp->maxline = dda->max_lines;
	dda_tmp->angle = dda->angle;
	dda_tmp->t = 0;
	dda_tmp->i = 0;
	dda_tmp->quality = (float)quality;
}

void	init_dist_x_y(t_vec2 *vec)
{
	vec->disty = 1 - (vec->y - (int)vec->y);
	vec->distx = 1 - (vec->x - (int)vec->x);
	if (vec->angle >= 0 && vec->angle <= 180)
		vec->disty = 1 - vec->disty;
	if (vec->disty == 0)
		vec->disty = 1;
	if (vec->angle >= 90 && vec->angle <= 270)
		vec->distx = 1 - vec->distx;
	if (vec->distx == 0)
		vec->distx = 1;
	vec->distx *= 10;
	vec->disty *= 10;
}

float	dda_dist(t_data *data, float angle, char *dir, bool *new_block)
{
	t_vec2	vector;

	vector.x = data->player->x + 0.5f;
	vector.y = data->player->y + 0.5f;
	angle = data->player->angle + angle;
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	vector.angle = angle;
	return (get_distance(vector, data, dir, new_block));
}
