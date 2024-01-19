/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:29:25 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/18 17:14:18 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/srcs/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define PURPLE "\x1B[1;35m"
# define GREEN "\x1B[1;32m"
# define BLUE "\x1B[1;34m"
# define WHITE "\x1B[1;37m"
# define RESET "\x1B[0m"
# define JSANGER_I "https://profile.intra.42.fr/users/jsanger"
# define SLIPPERT_I "https://profile.intra.42.fr/users/slippert"
# define JSANGER_G "https://github.com/Jano844"
# define SLIPPERT_G "https://github.com/Steven-L-42"
# define PI 3.14159265359
# define SIZE 100

# define NOD "NO textures/bricks/brick_purple.png\n"
# define SOD "SO textures/bricks/brick_red.png\n"
# define WED "WE textures/bricks/brick_orange.png\n"
# define EAD "EA textures/bricks/brick_green.png\n"
# define FD "F 225, 0, 0\n"
# define CD "C 135, 206, 125\n"

# define FLT_MAX 3.402823e+38
# define QUALITY 1
# define BLOCK_PIXEL_SIZE 256

typedef struct s_detection
{
	int				angle;
	int				x;
	int				y;
}					t_detection;

typedef struct s_directions
{
	int				forward;
	int				sideward;
}					t_directions;

typedef struct s_player
{
	t_directions	dir;
	char			start_direction;
	int				mouse_x;
	int				mouse_y;
	float			x;
	float			y;
	float			angle;
	float			prev_angle;
	float			view_angle;
	float			prev_mouse_x;
	double			prev_time;
	int				curr_item;
}					t_player;

typedef struct s_vec2
{
	float			x;
	float			y;
	float			angle;
	float			m;
	float			distx;
	float			disty;
	float			tempx;
	float			tempy;
}					t_vec2;

typedef struct s_rgba
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_rgba;

typedef struct s_map
{
	char			**tmp_map;
	char			**rnd_map;
	char			**map;
	char			**map_dda;
	int				width;
	int				height;
	int				skip_height;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*door;
	char			*f;
	char			*c;
	int				col_floor;
	int				col_ceiling;
	int				count_player;
	bool			is_random_map;
	bool			is_explored;
	int				cur_exp;
	int				pixel_unexp;
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
	float			shadow;
	uint32_t		col_floor;
	uint32_t		col_ceiling;
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
	float			width_array[1024];
}					t_dda;

typedef struct s_crosshair
{
	int				i;
	int				j;
	int				middle_x;
	int				middle_y;
	uint32_t		color;
	int				tmp_middle_x;
	int				radius;
}					t_crosshair;

typedef struct s_dda_dist
{
	float			dist;
	int				tempy;
	int				tempx;
	float			last_dist;
	float			m;
	char			last_dir;
	bool			xmin;
	bool			ymin;
	char			old_dir;
}					t_dda_dist;

typedef struct s_check_door
{
	int				instance;
	float			p_x_cos;
	float			p_y_sin;
	float			cell_x;
	float			cell_y;
	float			radian_angle;
}					t_check_door;

typedef struct s_calc_helper
{
	float			line;
	float			maxline;
	float			angle;
	float			t;
	float			dist;
	int				i;
	float			quality;
}					t_dda_helper;

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
	mlx_image_t		*img_splash_main;
	mlx_image_t		*img_splash_start;
	mlx_image_t		*img_mm_wall;
	mlx_image_t		*img_mm_walk;
	mlx_image_t		*img_mm_portal;
	mlx_image_t		*img_mm_door_closed;
	mlx_image_t		*img_mm_door_open;
	mlx_image_t		*img_mm_overlay;
	mlx_image_t		*img_mm_explored;
	mlx_image_t		*img_game_cursor;
	mlx_image_t		*img_player;
	mlx_image_t		*img_player_ray;
	mlx_image_t		*img_movement_ray;
	mlx_image_t		*img_game_wall;
	mlx_image_t		*img_crosshair;

	mlx_image_t		*img_door_closed;
	mlx_texture_t	*txt_door_closed;

	mlx_image_t		*img_no;
	mlx_texture_t	*txt_no;

	mlx_image_t		*img_so;
	mlx_texture_t	*txt_so;

	mlx_image_t		*img_we;
	mlx_texture_t	*txt_we;

	mlx_image_t		*img_ea;
	mlx_texture_t	*txt_ea;

	mlx_image_t		*img_bb;
	mlx_texture_t	*txt_bb;

	int				torch_frame;
	int				pistol_frame;
	mlx_image_t		*img_pistol[5];
	mlx_image_t		*img_torch[6];
}					t_img;

typedef struct s_data
{
	mlx_t			*mlx;
	t_img			*img;
	t_map			*game;
	t_minimap		*minimap;
	t_player		*player;
	t_detection		detc;
	int				cross_index;
	uint32_t		cross_colors[9];
	char			wall_type;
	uint32_t		color[64];
	int				wall_size[2];
	int				width;
	int				height;
	bool			is_shooting;
	bool			is_torching;
	bool			is_surrounded;
	bool			is_started;
}					t_data;

float				dda_dist(t_data *data, float angle, char *dir,
						bool *new_block);
// splash
void				ft_splash_to_game(t_data *data);
void				ft_start_game(t_data *data);
void				ft_open_image_splash(t_data *data);

// get_map
int					init_map(t_data *data, char *input);
void				draw_minimap(t_data *data);

// init_1
int					ft_init(t_data *data, char *input);

// init_2
void				init_coords(t_data *data, int pixel_x, int pixel_y);
void				init_player(t_data *data);
int					init_img_one(t_data *data);
int					init_img_two(t_data *data);

// utils dda
float				calc_for_x(float big, float small);
void				reset_map(t_data *data);
float				ft_get_block_width(t_dda *calc);
float				get_slope(float angle);

// utils main
void				ft_img_to_window(t_data *data);
void				reset_window(t_data *data);
void				ft_running(void *param);
int					ft_check_extension(char *argv);
void				draw_crosshair(t_data *data, uint32_t color);

// utils random
int					ft_create_random_map(t_data *data, char ***argv);

// utils map
int					get_map_height(char *input);
int					ft_map_len(char **tmp_map);
int					ft_str_to_rgb(char *rgb_str, int *color);
char				*ft_strtok(char *src, char delim, int x, int i);
int					ft_open_image(t_data *data, mlx_image_t **img_direction,
						char *img_path);
int					ft_open_image_keep_text(t_data *data,
						mlx_image_t **img_direction, mlx_texture_t **text,
						char *img_path);
int					ft_toktrim(char *rgb_str, char **r, char **g, char **b);
int					ft_count_comma(char *str);

// utils basic
int					ft_is_in_set(char c, const char *set);
int					ft_error(char *str);
int					ft_strlen_until(char *str, int c);
void				ft_change_item(t_data *data);

// utils math
int					ft_differ(int a, int b);
int					ft_is_alloc(char **map, int y, int x);
// utils free
void				ft_free_structs(t_data *data);
void				ft_free2d_char(char **str);
void				ft_free2d_int(int **str);
void				ft_exit(t_data *data, bool is_init);
void				ft_free2d_until(void **str, int max_len);
void				ft_check_free(char *str);
void				ft_check_free_text(mlx_texture_t *text);

// utils cross
void				draw_hori(t_data *data, t_crosshair cross);
void				draw_verti(t_data *data, t_crosshair cross);
void				draw_leftdiagonal(t_data *data, t_crosshair cross);
void				draw_rightdiagonal(t_data *data, t_crosshair cross);
void				draw_circle(t_data *data, t_crosshair cross);

// utils minimap
void				draw_map_explored(t_data *data, int r, int x, int y);
void				ft_check_is_explored(t_data *data);

// utils init
void				init_vars(t_data *data);

// utils color
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
uint32_t			**get_color(mlx_texture_t *texture);
uint32_t			ft_select_color(t_data *data, t_dda *calc, int block_height,
						int block_width);
uint32_t			ft_shadow_coloring(t_data *data, float start, int src_color,
						bool is_floor);

// utils detection
void				set_coords(t_data *data, t_draw_rays *ray, int ray_len);

// get_distance to wall
double				ray_distance(t_data *data, float angle);
void				dda_horizontal(t_data *data);

// movement
void				move_player(t_data *data, float speed, int forward);
void				ft_player_angle(double xpos, double ypos, void *param);

// hotkeys
void				ft_key_hold(void *param);
void				ft_key_press(mlx_key_data_t keydata, void *param);
void				ft_mouse_press(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param);
// animation
void				ft_torch_anim(void *param);
void				ft_pistol_anim(void *param);

// minimap
void				draw_player_rays(t_data *data, int num_rays);

// wall detection
void				check_for_door(t_data *data);
int					check_wall_ray(t_data *data);

// calc_view2
void				dda_vertical(t_data *data, t_dda *calc, bool if_true);

bool				ft_valid_map(char **copied_map);
void				initialize(int diff, int max_x_y[2], char **copied_map);
bool				ft_valid_chars(t_data *data, int max_y);
float				get_distance(t_vec2 vec, t_data *data, char *dir,
						bool *new_block);
char				**cpy_map(char **original, int size);
float				start_dist(t_vec2 *vec, char *dir, bool *xminus,
						bool *yminus);
void				init_dist_x_y(t_vec2 *vec);
void				inital(t_dda *dda, t_dda_helper *dda_tmp, float quality);

#endif
