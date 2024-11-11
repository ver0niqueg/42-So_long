/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:43:30 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 20:26:54 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	close_game(t_game *game)
{
	destroy_all(game, 0);
	return (0);
}

static void	start_game(t_game *game)
{
	add_sprites_to_map(game, 0, 0);
	mlx_key_hook(game->win_ptr, handle_keypress, game);
	mlx_hook(game->win_ptr, DestroyNotify, 0, close_game, game);
	mlx_loop(game->mlx_ptr);
}

static int	initialize_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
	{
		return (ft_printf
			(RED"Error\n"GREY"Failed to initialize graphics\n"RESET));
		return (free_all(game), 1);
	}
	mlx_get_screen_size(game->mlx_ptr, &game->max_x, &game->max_y);
	game->max_y = game->max_y / TILE;
	game->max_x = game->max_x / TILE;
	if (game->size_x > game->max_x || game->size_y > game->max_y)
	{
		(ft_printf(RED"Error\n"GREY"Map is too large for the screen\n"RESET));
		mlx_destroy_display(game->mlx_ptr);
		return (free_all(game), 1);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->size_x * TILE,
			game->size_y * TILE, "SO LONG");
	if (game->win_ptr == NULL)
	{
		return (ft_printf(RED"Error\n"GREY"Window creation failed\n"RESET));
		mlx_destroy_display(game->mlx_ptr);
		return (free_all(game), 1);
	}
	return (0);
}

static void	check_input(int argc, char *argv, t_game *game)
{
	if (argc != 2)
	{
		(ft_printf(RED"Error\n"GREY"Wrong number of arguments.\n"RESET));
		exit(1);
	}
	if (check_map_extension(argv) == 0)
	{
		(ft_printf
			(RED"Error\n"GREY"Wrong file extension. Use a .ber file\n"RESET));
		exit(1);
	}
	init_data(game);
	if (is_map_valid(argv, game) == 0)
		ft_error(NULL, game);
	free_temp(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_input(argc, argv[1], &game);
	if (initialize_mlx(&game) == 1)
		return (1);
	start_game(&game);
	return (0);
}
