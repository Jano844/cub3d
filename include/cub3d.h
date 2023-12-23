/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:29:25 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/22 23:02:32 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>
#include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/srcs/libft.h"

#define PI 3.14159265359
#define SIZE 100


typedef struct	s_player
{
	float	x;
	float	y;
	float	angle;
	float	view_angle;
}				t_player;

typedef struct	s_map
{
	char			**map;
	int				width;
	int				height;
}				t_map;

typedef struct	s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_map			*map;
	t_player		*player;
}				t_data;




// get_map
void	get_map(t_map *map, char *input);

// utils
void	ft_free2d(char **str);
void	ft_exit(t_data *data);
double	radians_to_degrees(double radians);
double	degrees_to_radians(double degrees);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

// get_distance to wall
float	ray_distance(t_data *data, float angle);

void	draw_triangle(t_data *data, float a, float h, int x, int y, int dir);

#endif
