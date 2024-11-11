/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:43:38 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 20:31:34 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	is_path_around(char **map, int i, int j)
{
	if (map[i + 1][j] != '.' && map[i - 1][j] != '.' && map[i][j + 1] != '.'
		&& map[i][j - 1] != '.')
		return (0);
	return (1);
}

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
