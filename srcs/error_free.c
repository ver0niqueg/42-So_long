/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:59:39 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 20:08:02 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_ptr(void **ptr)
{
	if (ptr == NULL)
		return ;
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_matrix(char ***matrix, int y)
{
	int	i;

	if (matrix == NULL || *matrix == NULL)
		return ;
	i = 0;
	while (i < y)
	{
		if ((*matrix)[i] != NULL)
		{
			free((*matrix)[i]);
			(*matrix)[i] = NULL;
		}
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

void	free_all(t_game *game)
{
	if (game->map != NULL)
		free_matrix(&game->map, game->size_y);
	if (game->mlx_ptr != NULL)
	{
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
}

void	free_temp(t_game *game)
{
	if (game->temp != NULL)
	{
		if (game->temp->line != NULL)
			free_ptr((void **)&game->temp->line);
		if (game->temp->item != NULL)
			free_ptr((void **)&game->temp->item);
		if (game->temp->map_check != NULL)
			free_matrix(&game->temp->map_check, game->temp->y);
		free(game->temp);
		game->temp = NULL;
	}
}

void	ft_error(char *str, t_game *game)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	if (game != NULL)
	{
		if (game->temp->fd_map != -1)
			manage_file(NULL, game, 'C');
		free_temp(game);
		free_all(game);
	}
	exit(1);
}
