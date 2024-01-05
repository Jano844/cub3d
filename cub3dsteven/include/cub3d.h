/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:29:25 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/05 04:25:19 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/srcs/libft.h"
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define PURPLE "\x1B[1;35m"
# define GREEN "\x1B[1;32m"
# define BLUE "\x1B[1;34m"
# define WHITE "\x1B[1;37m"
# define RESET "\x1B[0m"

# define PI 3.14159265359
# define SIZE 100

# define QUALITY 1
# define BLOCK_PIXEL_SIZE 128

typedef struct s_detection
{
	int				angle;
	int				x;
	int				y;
}					t_detection;

typedef struct s_player
{
	char			start_direction;
	int				mouse_x;
	int				mouse_y;
	float			x;
	float			y;
	float			angle;
	float			prev_angle;
	float			view_angle;
	float			prev_mouseX;
	double			prev_time;
}					t_player;

typedef struct s_rgb
{
	uint32_t		r;
	uint32_t		g;
	uint32_t		b;
}					t_rgb;

typedef struct s_map
{
	char			**tmp_map;
	char			**map;
	int				width;
	int				height;
	int				skip_height;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;

	char			*F;
	char			*C;
	int				color_floor;
	int				color_ceiling;
}					t_map;

typedef struct s_minimap
{
	int				**map;
	int				width;
	int				height;
}					t_minimap;

typedef struct s_calc_view
{
	char			direction;
	uint32_t		color_floor;
	uint32_t		color_ceiling;
	uint32_t		color_wall;
	uint32_t		color_door;
	uint32_t		color_portal;
	float			max_lines;
	float			temp2;
	float			j;
	float			angle;
	float			tmp;
	float			line;
	float			x;
	float			treshold;
	double			distance;
	double			line_bottom;
	double			line_top;
	float			width_array[100];
}					t_calc_view;

typedef struct s_draw_rays
{
	int				color;
	int				x_coord;
	int				y_coord;
	float			i;
	float			angle_offset;
}					t_draw_rays;

typedef struct s_img
{
	mlx_image_t		*img_game;
	mlx_image_t		*img_mm_wall;
	mlx_image_t		*img_mm_wall_shadow;
	mlx_image_t		*img_mm_portal;
	mlx_image_t		*img_mm_door_closed;
	mlx_image_t		*img_mm_door_open;
	mlx_image_t		*img_game_cursor;
	mlx_image_t		*img_player;
	mlx_image_t		*img_player_ray;
	mlx_image_t		*img_game_wall;
	mlx_image_t		*img_NO;
	uint32_t		*col_NO;
	mlx_image_t		*img_SO;
	uint32_t		*col_SO;
	mlx_image_t		*img_WE;
	uint32_t		*col_WE;
	mlx_image_t		*img_EA;
	uint32_t		*col_EA;

	int				pistol_frame;
	mlx_image_t		*img_pistol[5];
}					t_img;

typedef struct s_data
{
	mlx_t			*mlx;
	t_img			*img;
	t_map			*game;
	t_minimap		*minimap;
	t_player		*player;
	t_detection		detec;

	char			wall_type;
	uint32_t		color[64];
	int				wall_size[2];
	int				width;
	int				height;
	bool			is_shooting;
}					t_data;

float				calc_dist(t_data *data, float angle, char *dir, bool *new_block);

// get_map
int					init_map(t_data *data, char *input);
void				draw_minimap(t_data *data);

// init_1
int					init(t_data *data, char *input);

// init_2
void				init_coords(t_data *data, int pixel_x, int pixel_y);
void				init_player(t_data *data);
int					init_img_one(t_data *data);
int					init_img_two(t_data *data);

// utils main
void				ft_img_to_window(t_data *data);
void				reset_window(t_data *data);
void				ft_running(void *param);
int					ft_check_extension(char *argv);

// utils map
int					get_map_height(char *input);
int					ft_map_len(char **tmp_map);
int					ft_str_to_rgb(char *rgb_str, int *color);
char				*ft_strtok(char *src, char delim);
int					ft_open_image(t_data *data, mlx_image_t **img_direction,
						char *img_path);
int					ft_open_image_plus_info(t_data *data,
						mlx_image_t **img_direction, uint32_t **color,
						char *img_path);
// utils basic
int					ft_is_in_set(char c, const char *set);
int					ft_error(char *str);

// utils free
void				free_structs(t_data *data);
void				ft_free2d_char(char **str);
void				ft_free2d_int(int **str);
void				ft_exit(t_data *data);

// utils color
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int					get_colour_from_pixel(u_int8_t *pixel);
void				hex_to_rgb(char *hex, int *r, int *g, int *b);
uint32_t			*get_color(mlx_texture_t *texture);

// get_distance to wall
double				ray_distance(t_data *data, float angle);
void				calc_view(t_data *data);

// movement
void				update_player_angle(double xpos, double ypos, void *param);


// hotkeys
void				ft_key_hold(void *param);
void				ft_key_press(mlx_key_data_t keydata, void *param);
void				ft_mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void* param);

// minimap
void				draw_player_rays(t_data *data, int num_rays);

// wall detection
void				check_for_door(t_data *data);
int					check_for_wall(t_data *data, float distance,
						float radian_angle, const char *set);
int					check_wall_corner_behind(t_data *data, const char *set);
int					check_wall_corner_ahead(t_data *data, const char *set);

// calc_view2
void				draw_texture(t_data *data, t_calc_view *calc, bool if_true);

#endif
