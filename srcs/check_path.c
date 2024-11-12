/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:43:38 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/12 11:52:26 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* fonction qui check si une case specifiee est accessible depuis une autre
case atteignable, marquee par .'' */
static int	is_path_around(char **map, int i, int j)
{
	if (map[i + 1][j] != '.' && map[i - 1][j] != '.' && map[i][j + 1] != '.'
		&& map[i][j - 1] != '.')
		return (0);
	return (1);
}

/* fonction qui implemente l'algorithme de flood fill pour explorer la map et
marquer les zones atteignables a partir d'une position donnee */
static void	flood_fill(t_game *game, int y, int x)
{
	if (y <= 0 || y >= game->temp->y - 1 || x <= 0 || x >= game->temp->x - 1)
		return ;
	if (game->temp->map_check[y][x] == '.' || game->temp->map_check[y][x] == '1'
		|| game->temp->map_check[y][x] == 'E')
		return ;
	if (game->temp->map_check[y][x] == 'C')
		game->item_found++;
	game->temp->map_check[y][x] = '.';
	flood_fill(game, y - 1, x);
	flood_fill(game, y + 1, x);
	flood_fill(game, y, x - 1);
	flood_fill(game, y, x + 1);
}

/* fonction qui check que la sortie est accessible et les collectibles tous
atteignables par le joueur */
int	check_path(t_game *game)
{
	int	i;
	int	j;

	flood_fill(game, game->player_y, game->player_x);
	i = 1;
	while (i < game->temp->y - 1)
	{
		j = 1;
		while (game->temp->map_check[i][j])
		{
			if (game->temp->map_check[i][j] == 'E'
				&& is_path_around(game->temp->map_check, i, j) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (game->item_count != game->item_found)
		return (0);
	game->item_found = 0;
	return (1);
}
