/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:00:11 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 15:05:59 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_extension(char *argv)
{
	int	start;

	start = ft_strlen(argv) - 4;
	if (ft_strnstr(&argv[start], ".ber", 4) == NULL)
		return (0);
	return (1);
}

/*
**	To avoid checking inside walls :
**	i = 1; to start from second row of the map,
**	j = 1; to start from second column of the map.
**
**	Inside temp->item[2] = {0, 0};
**	item[0] for player,
**	item[1] for exit.
*/
static int	check_map_items(t_data *data, int i, int j)
{
	while (i++ < data->temp->y - 1)
	{
		j = 0;
		while (j++ < data->temp->x - 1)
		{
			if (data->temp->map_check[i][j] == 'C')
				data->item_count++;
			else if (data->temp->map_check[i][j] == 'P')
			{
				data->player_y = i;
				data->player_x = j;
				data->temp->item[0]++;
			}
			else if (data->temp->map_check[i][j] == 'E')
				data->temp->item[1]++;
			else if (data->temp->map_check[i][j] != '0'
				&& data->temp->map_check[i][j] != '1')
				return (0);
		}
	}
	if (data->temp->item[0] != 1 || data->temp->item[1] != 1
		|| data->item_count < 1)
		return (0);
	return (1);
}

/*
**	Checks if there is a wall at line[0] and line[x - 1],
**	checks if only walls on the first and last line.
*/
static int	check_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->temp->y)
	{
		if (data->temp->map_check[i][0] != '1'
			|| data->temp->map_check[i][data->temp->x - 1] != '1')
			return (0);
		j = 0;
		if (i == 0 || i == data->temp->y - 1)
		{
			while (j < data->temp->x)
			{
				if (data->temp->map_check[i][j] != '1')
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

static int	check_map_size(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->temp->y)
	{
		if ((size_t)data->temp->x != ft_strlen(data->temp->map_check[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
**	1-	Counts map lines + inits x and y for map dimensions.
**	2- 	Fills **map_check and **map with file.ber content.
**	3- 	Checks if map is rectangular.
**	4- 	Checks if only 1 [wall] on map sides.
**	5- 	Checks for 0 [empty], C [collectible], P [player], and E [exit].
**	6- 	Checks if E and C are accessible.
*/
int	is_map_valid(char *argv, t_data *data)
{
	if (count_lines(argv, data) == 0)
		return (ft_putstr_fd("Error\nInvalid map file.\n", 2), 0);
	fill_matrix(argv, data, 0);
	if (check_map_size(data) == 0)
		return (ft_putstr_fd("Error\nMap must be rectangular.\n", 2), 0);
	if (check_walls(data) == 0)
		return (ft_putstr_fd("Error\nMap must be surrounded by 1.\n", 2), 0);
	if (check_map_items(data, 0, 0) == 0)
		return (ft_putstr_fd("Error\nItem conditions not met.\n", 2), 0);
	if (check_path(data) == 0)
		return (ft_putstr_fd("Error\nExit/Collectibles not on path.\n", 2), 0);
	return (1);
}