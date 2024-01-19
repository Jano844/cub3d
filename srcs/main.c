/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:24:02 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/18 16:49:39 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_leaks(void)
{
	system("leaks cub3D");
}

void	ft_instructions(t_data *data)
{
	int	i;

	i = 0;
	write(1, "\n", 1);
	while (data->game->map[i])
		ft_printf("%s\n", data->game->map[i++]);
	ft_printf("%s\nPlayer Movement:\tW | A | S | D\n", PURPLE);
	ft_printf("Player Rotation:\tArrow Keys | Mouse\n");
	ft_printf("Player Run:\t\tLeft Shift\n");
	ft_printf("-------------------------------------------------\n");
	ft_printf("Weapon Fire:\t\tSpace\t| Mouse LB\n");
	ft_printf("Change Crosshair:\tPage UP\t| Page DOWN\n");
	ft_printf("Toggle Torch:\t\tF\t| Mouse MB\n");
	ft_printf("%s\nproject by:\n\n%s", GREEN, RESET);
	ft_printf("%sjsanger:\t\033]8;;%s\033\\(Intra)\033]8;;\033\\ && ", BLUE,
		JSANGER_I);
	ft_printf("\033]8;;%s\033\\(GitHub)\033]8;;\033\\\n", JSANGER_G);
	ft_printf("%s------------------------------------\n%s", WHITE, RESET);
	ft_printf("%sslippert:\t\033]8;;%s\033\\(Intra)\033]8;;\033\\ && ", BLUE,
		SLIPPERT_I);
	ft_printf("\033]8;;%s\033\\(GitHub)\033]8;;\033\\%s\n\n", SLIPPERT_G,
		RESET);
}

int	ft_alloc_structs(t_data *data)
{
	data->game = malloc(sizeof(t_map));
	if (!data->game)
		return (ft_free_structs(data),
			ft_error("Error: data->game allocation failed!"));
	data->minimap = malloc(sizeof(t_minimap));
	if (!data->minimap)
		return (ft_free_structs(data),
			ft_error("Error: data->minimap allocation failed!"));
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (ft_free_structs(data),
			ft_error("Error: data->player allocation failed!"));
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		return (ft_free_structs(data),
			ft_error("Error: data->img allocation failed!"));
	data->player->curr_item = 0;
	return (0);
}

int	ft_main_checks(t_data *data, int argc, char **argv)
{
	if (!data)
		return (ft_error("Error: data allocation failed!"));
	if (ft_alloc_structs(data))
		return (1);
	if (argc != 2 || (argc == 2 && ft_check_extension(*(argv + 1))))
		return (ft_free_structs(data), 1);
	if (ft_init(data, argv[1]))
		return (ft_exit(data, 1), 1);
	return (0);
}

// atexit(ft_leaks);
int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (ft_main_checks(data, argc, argv))
		exit(1);
	ft_instructions(data);
	ft_img_to_window(data);
	mlx_loop_hook(data->mlx, ft_running, data);
	mlx_cursor_hook(data->mlx, ft_player_angle, data);
	mlx_key_hook(data->mlx, ft_key_press, data);
	mlx_loop_hook(data->mlx, ft_key_hold, data);
	mlx_loop_hook(data->mlx, ft_pistol_anim, data);
	mlx_loop_hook(data->mlx, ft_torch_anim, data);
	mlx_mouse_hook(data->mlx, ft_mouse_press, data);
	mlx_loop(data->mlx);
	ft_exit(data, 0);
	exit(0);
}
