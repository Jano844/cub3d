/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:40:45 by slippert          #+#    #+#             */
/*   Updated: 2024/01/13 14:37:09 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_vars(t_data *data)
{
	data->player->mouse_y = 0;
	data->player->mouse_x = 0;
	data->game->no = NULL;
	data->game->so = NULL;
	data->game->we = NULL;
	data->game->ea = NULL;
	data->game->c = NULL;
	data->game->f = NULL;
	data->img->txt_no = NULL;
	data->img->txt_so = NULL;
	data->img->txt_we = NULL;
	data->img->txt_ea = NULL;
	data->img->txt_door_closed = NULL;
	data->game->tmp_map = NULL;
	data->game->rnd_map = NULL;
	data->game->map = NULL;
	data->game->map_dda = NULL;
	data->minimap->map = NULL;
	data->is_started = false;
	data->is_torching = false;
	data->is_surrounded = false;
	data->game->width = 0;
	data->game->pixel_unexp = 0;
	data->game->is_random_map = false;
}
