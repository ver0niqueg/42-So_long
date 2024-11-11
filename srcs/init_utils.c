/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:36:00 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 20:08:51 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	init_temp(t_game *game)
{
	game->temp = ft_calloc(1, sizeof(t_temp));
	check_alloc(game->temp, NULL);
	game->temp->item = ft_calloc(2, sizeof(int));
	check_alloc(game->temp->item, game);
	game->temp->x = 0;
	game->temp->y = 0;
	game->temp->fd_map = -1;
	game->temp->map_check = NULL;
	game->temp->line = NULL;
}

void	init_data(t_game *game)
{
	game->move_counter = 1;
	game->item_count = 0;
	game->item_found = 0;
	game->on_exit = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->size_x = 0;
	game->size_y = 0;
	game->max_x = 0;
	game->max_y = 0;
	game->img_x = 0;
	game->img_y = 0;
	game->map = NULL;
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->sprite = NULL;
	init_temp(game);
}

void	alloc_matrix(char ***matrix, t_game *game)
{
	*matrix = ft_calloc(game->temp->y, sizeof(char *));
	check_alloc(*matrix, game);
}

void	check_alloc(void *ptr, t_game *game)
{
	if (ptr == NULL)
		ft_error(RED"Error\n"GREY"Failed to allocate memory\n", game);
}

void	check_sprites_alloc(t_game *game)
{
	if (!game->sprite->wall || !game->sprite->wall || !game->sprite->floor
		|| !game->sprite->player
		|| !game->sprite->closed_exit
		|| !game->sprite->opened_exit)
	{
		ft_printf(RED"Error\n"GREY"Failed to allocate memory for sprites\n");
		destroy_all(game, 1);
	}
}
