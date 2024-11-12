/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:19:45 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/12 12:35:51 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* fonction qui maj l'affichage du sprite du joueur en fonction de sa position
sur la map */
void	update_sprite(t_game *game)
{
	if (game->map[game->player_y][game->player_x] == '0')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->sprite->floor, game->player_x * TILE, game->player_y * TILE);
	if (game->map[game->player_y][game->player_x] == 'P')
		add_player(game, game->player_y, game->player_x);
}

/* fonction qui gere le chargement des images necessaires pour afficher
les elements de la map sur la fenetre graphique */
void	assign_all_sprites(t_game *game)
{
	game->sprite->wall = mlx_xpm_file_to_image(game->mlx_ptr, WALL,
			&game->img_x, &game->img_y);
	game->sprite->floor = mlx_xpm_file_to_image(game->mlx_ptr, FLOOR,
			&game->img_x, &game->img_y);
	game->sprite->player = mlx_xpm_file_to_image(game->mlx_ptr, PLAYER,
			&game->img_x, &game->img_y);
	game->sprite->star = mlx_xpm_file_to_image(game->mlx_ptr, STAR,
			&game->img_x, &game->img_y);
	game->sprite->closed_exit = mlx_xpm_file_to_image(game->mlx_ptr,
			CLOSED_EXIT, &game->img_x, &game->img_y);
	game->sprite->opened_exit = mlx_xpm_file_to_image(game->mlx_ptr,
			OPENED_EXIT, &game->img_x, &game->img_y);
	check_sprites_alloc(game);
}

/* fonction qui libere les ressources graphiques allouees pour les sprites */
void	destroy_all_sprites(t_game *game)
{
	if (game->sprite != NULL)
	{
		if (game->sprite->wall != NULL)
			mlx_destroy_image(game->mlx_ptr, game->sprite->wall);
		if (game->sprite->floor != NULL)
			mlx_destroy_image(game->mlx_ptr, game->sprite->floor);
		if (game->sprite->player != NULL)
			mlx_destroy_image(game->mlx_ptr, game->sprite->player);
		if (game->sprite->star != NULL)
			mlx_destroy_image(game->mlx_ptr, game->sprite->star);
		if (game->sprite->opened_exit != NULL)
			mlx_destroy_image(game->mlx_ptr, game->sprite->closed_exit);
		if (game->sprite->closed_exit != NULL)
			mlx_destroy_image(game->mlx_ptr, game->sprite->opened_exit);
		free(game->sprite);
		game->sprite = NULL;
	}
}
