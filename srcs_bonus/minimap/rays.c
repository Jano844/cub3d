/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:49:49 by slippert          #+#    #+#             */
/*   Updated: 2024/01/13 14:51:38 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Funktion: ray_helper
// Zweck: Hilfsfunktion für die Berechnung und Darstellung einzelner Rays.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - ray: Zeiger auf die Struktur,
//	die Informationen über die zu zeichnenden Rays enthält.
//
// Die Funktion iteriert über eine maximale Anzahl von Schritten, um die
// Koordinaten jedes einzelnen Rays zu berechnen. Sie überprüft dann,
// ob die berechneten Koordinaten im gültigen Bereich liegen und ob es
// Kollisionen mit Wänden gibt. Bei gültigen Koordinaten wird die
// entsprechende Pixelposition im Bildspeicher markiert.
static void	ray_helper(t_data *data, t_draw_rays *ray)
{
	int	ray_len;
	int	max_len;

	max_len = 125;
	if (data->is_torching || data->is_shooting)
		max_len = 225;
	ray_len = -1;
	while (++ray_len < max_len)
	{
		ray->x_coord = data->player->x * 16 + 8 + ray_len
			* cos((-data->player->angle + ray->angle_offset) * PI / 180);
		ray->y_coord = data->player->y * 16 + 8 + ray_len
			* sin((-data->player->angle + ray->angle_offset) * PI / 180);
		if (ray->x_coord >= 0 && ray->y_coord >= 0
			&& (const uint32_t)ray->x_coord < data->img->img_player_ray->width
			&& (const uint32_t)ray->y_coord < data->img->img_player_ray->height)
		{
			if (!ft_is_alloc(data->game->map, ray->y_coord / 16, ray->x_coord
					/ 16) || ft_is_in_set(data->game->map[ray->y_coord
						/ 16][ray->x_coord / 16], "15 "))
				break ;
			mlx_put_pixel(data->img->img_player_ray, ray->x_coord, ray->y_coord,
				ray->color);
		}
	}
}

// Funktion: draw_player_rays
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - num_rays: Die Anzahl der Rays, die gezeichnet werden sollen.
//
// Die Funktion iteriert über alle Rays und berechnet Positionen/Endpunkte.
// Für jeden Ray wird dann die Hilfsfunktion ray_helper aufgerufen, die
// die Berechnungen für einzelne Rays durchführt.
void	draw_player_rays(t_data *data, int num_rays)
{
	t_draw_rays	ray;

	ft_memset(data->img->img_player_ray->pixels, 0,
		data->img->img_player_ray->width * data->img->img_player_ray->height
		* sizeof(int32_t));
	ray.color = ft_pixel(247, 225, 178, 125);
	ray.i = -num_rays / 2;
	while (ray.i <= num_rays / 2)
	{
		ray.angle_offset = ray.i;
		ray_helper(data, &ray);
		ray.i += 0.1f;
	}
}
