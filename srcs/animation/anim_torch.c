/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_torch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/09 15:36:17 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_torch_anim(void *param)
{
	t_data		*data;
	int			i;
	static int	slower = 0;

	data = (void *)param;
	if (data->player->curr_item == 1 && slower++ > 3)
	{
		slower = 0;
		i = 0;
		while (i < 6)
		{
			if (data->img->torch_frame == i)
				data->img->img_torch[i++]->enabled = true;
			else
				data->img->img_torch[i++]->enabled = false;
		}
		data->img->torch_frame++;
		data->img->torch_frame = data->img->torch_frame % 6;
	}
}
