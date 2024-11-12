/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:39:54 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/12 12:28:54 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* fonctions qui utilisent mlx_put_image_to_window pour afficher les sprites
sur la fenetre de jeu */

void	add_floor(t_game *game, int y, int x)
{
	if (game->map[y][x] == '0')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->sprite->floor, x * TILE, y * TILE);
}

void	add_wall(t_game *game, int y, int x)
{
	if (game->map[y][x] == '1')
	{
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->sprite->wall, x * TILE, y * TILE);
	}
}

void	add_collectible(t_game *game, int y, int x)
{
	if (game->map[y][x] == 'C')
	{
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->sprite->star, x * TILE, y * TILE);
	}
}

void	add_player(t_game *game, int y, int x)
{
	if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->sprite->player, x * TILE, y * TILE);
}

void	add_closed_exit(t_game *game, int y, int x)
{
	if (game->map[y][x] == 'E')
	{
		game->exit_y = y;
		game->exit_x = x;
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->sprite->closed_exit, x * TILE, y * TILE);
	}
}
