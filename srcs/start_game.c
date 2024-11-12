/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:23:00 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/12 12:42:19 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* fonction qui nettoie et libere toutes les ressources utilisees par le jeu
avant sa fermeture */
void	destroy_all(t_game *game, int error)
{
	destroy_all_sprites(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_loop_end(game->mlx_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free_all(game);
	if (error == 1)
		exit(1);
	else
	{
		ft_printf("Thank you for playing !\n");
		exit(0);
	}
}

static void	add_opened_exit(t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->sprite->opened_exit, game->exit_x * TILE, game->exit_y * TILE);
}

/* fonction qui gere les deplacements du joueur en fonction des cases
qu'il rencontre */
void	move_player(t_game *game, int y, int x)
{
	static int	is_exit_open = 0;

	if (game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'C')
		game->item_found++;
	if (game->map[y][x] == 'E' && game->item_found != game->item_count)
	{
		ft_printf("You must collect all the items first!\n");
		return ;
	}
	if (game->map[y][x] == 'E' && game->item_found == game->item_count)
	{
		game->on_exit = 1;
		return ;
	}
	if (game->item_found == game->item_count && is_exit_open++ == 0)
		add_opened_exit(game);
	game->map[game->player_y][game->player_x] = '0';
	update_sprite(game);
	game->player_y = y;
	game->player_x = x;
	game->map[game->player_y][game->player_x] = 'P';
	update_sprite(game);
	ft_printf("Moves : %d\n", game->move_counter++);
}

/* fonction qui gere les evenements du clavier */
int	handle_keypress(int keycode, t_game *game)
{
	int	y;
	int	x;

	y = game->player_y;
	x = game->player_x;
	if (keycode == XK_Escape)
		close_game(game);
	if (keycode == XK_w)
		move_player(game, y - 1, x);
	else if (keycode == XK_s)
		move_player(game, y + 1, x);
	else if (keycode == XK_a)
		move_player(game, y, x - 1);
	else if (keycode == XK_d)
		move_player(game, y, x + 1);
	if (game->on_exit == 1)
	{
		ft_printf("Moves : %d\n", game->move_counter);
		ft_printf(GREEN"You win !\n"RESET);
		close_game(game);
	}
	return (0);
}

/* fonction qui ajoute les sprites au jeu */
void	add_sprites_to_map(t_game *game, int y, int x)
{
	game->sprite = ft_calloc(1, sizeof(t_sprite));
	if (game->sprite == NULL)
	{
		ft_printf(RED"Error\n"GREY"Memory allocation failed\n"RESET);
		destroy_all(game, 1);
	}
	assign_all_sprites(game);
	while (y < game->size_y)
	{
		x = 0;
		while (x < game->size_x)
		{
			add_floor(game, y, x);
			add_wall(game, y, x);
			add_collectible(game, y, x);
			add_player(game, y, x);
			add_closed_exit(game, y, x);
			x++;
		}
		y++;
	}
}
