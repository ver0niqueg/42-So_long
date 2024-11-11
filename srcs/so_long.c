/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:43:30 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 16:22:29 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	close_game(t_data *data)
{
	destroy_all(data, 0);
	return (0);
}

static void	start_game(t_data *data)
{
	add_images_to_map(data, 0, 0);
	mlx_key_hook(data->win_ptr, on_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, close_game, data);
	mlx_loop(data->mlx_ptr);
}

static int	initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		return (ft_printf(RED"Error\n"GREY"Failed to initialize graphics\n"RESET));
		return (free_all(data), 1);
	}
	mlx_get_screen_size(data->mlx_ptr, &data->max_x, &data->max_y);
	data->max_y = data->max_y / TILE;
	data->max_x = data->max_x / TILE;
	if (data->size_x > data->max_x || data->size_y > data->max_y)
	{
		(ft_printf(RED"Error\n"GREY"Map is too large for the screen\n"RESET));
		mlx_destroy_display(data->mlx_ptr);
		return (free_all(data), 1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->size_x * TILE,
			data->size_y * TILE, "SO LONG");
	if (data->win_ptr == NULL)
	{
		return (ft_printf(RED"Error\n"GREY"Window creation failed\n"RESET));
		mlx_destroy_display(data->mlx_ptr);
		return (free_all(data), 1);
	}
	return (0);
}

static void	check_input(int argc, char *argv, t_data *data)
{
	if (argc != 2)
	{
		(ft_printf(RED"Error\n"GREY"Wrong number of arguments.\n"RESET));
		exit(1);
	}
	if (check_extension(argv) == 0)
	{
		(ft_printf(RED"Error\n"GREY"Wrong file extension. Use a .ber file\n"RESET));
		exit(1);
	}
	init_data(data);
	if (is_map_valid(argv, data) == 0)
		ft_error(NULL, data);
	free_temp(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_input(argc, argv[1], &data);
	if (initialize_mlx(&data) == 1)
		return (1);
	start_game(&data);
	return (0);
}
