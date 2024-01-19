/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:19:39 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/18 16:50:18 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	back_condistion_block(t_data *data, t_dda_dist *dst,
			bool *new_block, char *dir)
{
	if (ft_is_alloc(data->game->map_dda, dst->tempy, dst->tempx) && \
		data->game->map_dda[dst->tempy][dst->tempx] == 'L')
		*new_block = false;
	if ((ft_is_alloc(data->game->map_dda, dst->tempy, dst->tempx) && \
			ft_is_in_set(data->game->map_dda[dst->tempy][dst->tempx], "15")) \
			|| *dir != dst->old_dir)
	{
		data->game->map_dda[dst->tempy][dst->tempx] = 'L';
		*new_block = true;
	}
	if (ft_is_alloc(data->game->map, dst->tempy, dst->tempx) && \
			data->game->map[dst->tempy][dst->tempx] == '5')
		data->wall_type = 'D';
	else
		data->wall_type = 'W';
}

void	first_init(t_dda_dist *dst, t_vec2 *vec)
{
	dst->dist = 0;
	dst->tempy = vec->y;
	dst->tempx = vec->x;
	dst->last_dist = dst->dist;
	vec->m = fabs(get_slope(vec->angle));
}

void	second_init(t_dda_dist *dst, t_vec2 vec, char *dir)
{
	dst->ymin = false;
	dst->xmin = false;
	dst->tempy = vec.y;
	dst->tempx = vec.x;
	dst->last_dist = dst->dist;
	dst->last_dir = *dir;
}

void	loop_condition(t_dda_dist *dst, t_vec2 *vec)
{
	if (dst->xmin == true && dst->ymin == true)
	{
		dst->tempx = ceil(vec->x) - 1;
		dst->tempy = ceil(vec->y) - 1;
	}
	else
	{
		if (dst->xmin == true)
			dst->tempx = ceil(vec->x) - 1;
		if (dst->ymin == true)
			dst->tempy = ceil(vec->y) - 1;
	}
}

float	get_distance(t_vec2 vec, t_data *data, char *dir, bool *new_block)
{
	t_dda_dist	dst;
	static char	old_dir;

	first_init(&dst, &vec);
	while ((ft_is_alloc(data->game->map, dst.tempy, dst.tempx) && \
			!ft_is_in_set(data->game->map[dst.tempy][dst.tempx], "15")) || \
			(ft_is_alloc(data->game->map_dda, dst.tempy, dst.tempx) && \
			!ft_is_in_set(data->game->map_dda[dst.tempy][dst.tempx], "15L")))
	{
		second_init(&dst, vec, dir);
		if (!ft_is_alloc(data->game->map, dst.tempy, dst.tempx) || \
			!ft_is_alloc(data->game->map_dda, dst.tempy, dst.tempx))
			return (1);
		dst.dist += fabs(start_dist(&vec, dir, &dst.xmin, &dst.ymin));
		dst.tempy = vec.y;
		dst.tempx = vec.x;
		loop_condition(&dst, &vec);
	}
	dst.old_dir = (char)old_dir;
	back_condistion_block(data, &dst, new_block, dir);
	old_dir = *dir;
	return (fabs(dst.dist));
}
