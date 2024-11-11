/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:43:38 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 15:07:00 by vgalmich         ###   ########.fr       */
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

/*
**	Fills accessible path (0, C) with '.' (as visited),
**	returns when current path is already filled,
**	stops when all map is filled.
*/
static void	flood_fill(t_data *data, int y, int x)
{
	if (y <= 0 || y >= data->temp->y - 1 || x <= 0 || x >= data->temp->x - 1)
		return ;
	if (data->temp->map_check[y][x] == '.' || data->temp->map_check[y][x] == '1'
		|| data->temp->map_check[y][x] == 'E')
		return ;
	if (data->temp->map_check[y][x] == 'C')
		data->item_found++;
	data->temp->map_check[y][x] = '.';
	flood_fill(data, y - 1, x);
	flood_fill(data, y + 1, x);
	flood_fill(data, y, x - 1);
	flood_fill(data, y, x + 1);
}

/*
**	To avoid iterating inside walls :
**	i = 1; to start from second row of the map,
**	j = 1; to start from second column of the map.
**
**	is_path_around checks if the exit is accessible.
*/
int	check_path(t_data *data)
{
	int	i;
	int	j;

	flood_fill(data, data->player_y, data->player_x);
	i = 1;
	while (i < data->temp->y - 1)
	{
		j = 1;
		while (data->temp->map_check[i][j])
		{
			if (data->temp->map_check[i][j] == 'E'
				&& is_path_around(data->temp->map_check, i, j) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (data->item_count != data->item_found)
		return (0);
	data->item_found = 0;
	return (1);
}
