/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:00:11 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/12 11:46:42 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* fonction qui check le bon format .ber du fichier en argument */
int	check_map_extension(char *argv)
{
	int	start;

	start = ft_strlen(argv) - 4;
	if (ft_strnstr(&argv[start], ".ber", 4) == NULL)
		return (0);
	return (1);
}

/* fonction qui check la presence et le nb des elements essentiels (joueur,
sortie et collectibles) dans la map */
static int	check_map_items(t_game *game, int i, int j)
{
	while (i++ < game->temp->y - 1)
	{
		j = 0;
		while (j++ < game->temp->x - 1)
		{
			if (game->temp->map_check[i][j] == 'C')
				game->item_count++;
			else if (game->temp->map_check[i][j] == 'P')
			{
				game->player_y = i;
				game->player_x = j;
				game->temp->item[0]++;
			}
			else if (game->temp->map_check[i][j] == 'E')
				game->temp->item[1]++;
			else if (game->temp->map_check[i][j] != '0'
				&& game->temp->map_check[i][j] != '1')
				return (0);
		}
	}
	if (game->temp->item[0] != 1 || game->temp->item[1] != 1
		|| game->item_count < 1)
		return (0);
	return (1);
}

/* fonction qui check que la map est bien entouree de murs, pour
s'assurer que le joueur ne peut pas sortir de la zone de jeu */
static int	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->temp->y)
	{
		if (game->temp->map_check[i][0] != '1'
			|| game->temp->map_check[i][game->temp->x - 1] != '1')
			return (0);
		j = 0;
		if (i == 0 || i == game->temp->y - 1)
		{
			while (j < game->temp->x)
			{
				if (game->temp->map_check[i][j] != '1')
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

/* fonction qui check que chaque ligne de le map a la meme taille pour que
la map soit rectangulaire */
static int	check_map_size(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->temp->y)
	{
		if ((size_t)game->temp->x != ft_strlen(game->temp->map_check[i]))
			return (0);
		i++;
	}
	return (1);
}

/* fonction qui check toutes les conditions requises pour que la map soit
valide */
int	is_map_valid(char *argv, t_game *game)
{
	if (count_lines(argv, game) == 0)
		return (ft_printf(RED"Error\n"GREY"Invalid Map\n"RESET), 0);
	fill_matrix(argv, game, 0);
	if (check_map_size(game) == 0)
		return (ft_printf(RED"Error\n"GREY"Map must be rectangular\n"RESET), 0);
	if (check_walls(game) == 0)
		return (ft_printf
			(RED"Error\n"GREY"Map must be surrounded by walls\n"RESET), 0);
	if (check_map_items(game, 0, 0) == 0)
		return (ft_printf
			(RED"Error\n"GREY"Items conditions are not met\n"RESET), 0);
	if (check_path(game) == 0)
		return (ft_printf
			(RED"Error\n"GREY"Exit/Items are not accessible\n"RESET), 0);
	return (1);
}
