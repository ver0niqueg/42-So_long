/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:23:42 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 20:29:14 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	count_lines(char *argv, t_game *game)
{
	manage_file(argv, game, 'O');
	while (game->temp->fd_map > 0)
	{
		game->temp->line = get_next_line(game->temp->fd_map);
		if (game->temp->line == NULL)
		{
			manage_file(NULL, game, 'C');
			break ;
		}
		if (game->temp->line[0] == '\n' && game->temp->line[1] == '\0')
			return (0);
		game->temp->y++;
		free_ptr((void **)&game->temp->line);
	}
	game->size_y = game->temp->y;
	if (game->temp->y < 3)
		return (0);
	return (1);
}

static void	check_last_line(t_game *game, char *line, int i)
{
	if (i == game->temp->y - 1)
	{
		if (ft_getnl(line) != NULL)
			ft_error(RED"Error\n"GREY"Invalid Map\n", game);
	}
}

void	fill_matrix(char *argv, t_game *game, int i)
{
	alloc_matrix(&game->temp->map_check, game);
	manage_file(argv, game, 'O');
	while (i < game->temp->y)
	{
		game->temp->line = get_next_line(game->temp->fd_map);
		check_alloc(game->temp->line, game);
		check_last_line(game, game->temp->line, i);
		game->temp->map_check[i] = ft_strtrim(game->temp->line, "\n");
		check_alloc(game->temp->map_check[i], game);
		game->temp->x = ft_strlen(game->temp->map_check[i]);
		game->size_x = game->temp->x;
		free_ptr((void **)&game->temp->line);
		i++;
	}
	manage_file(NULL, game, 'C');
	alloc_matrix(&game->map, game);
	i = 0;
	while (i < game->temp->y)
	{
		game->map[i] = ft_strdup(game->temp->map_check[i]);
		check_alloc(game->map[i], game);
		i++;
	}
}

void	manage_file(char *argv, t_game *game, int flag)
{
	if (flag == 'O')
	{
		game->temp->fd_map = open(argv, O_RDONLY);
		if (game->temp->fd_map == -1)
			ft_error(RED"Error\n"GREY"File issue\n", game);
	}
	else if (flag == 'C')
	{
		if (game->temp->fd_map != -1)
		{
			close(game->temp->fd_map);
			game->temp->fd_map = -1;
		}
	}
}

char	*ft_getnl(char *str)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (str);
		i++;
	}
	return (NULL);
}
