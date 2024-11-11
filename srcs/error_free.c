/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:59:39 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 15:09:18 by vgalmich         ###   ########.fr       */
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

void	free_all(t_data *data)
{
	if (data->map != NULL)
		free_matrix(&data->map, data->size_y);
	if (data->mlx_ptr != NULL)
	{
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
}

void	free_temp(t_data *data)
{
	if (data->temp != NULL)
	{
		if (data->temp->line != NULL)
			free_ptr((void **)&data->temp->line);
		if (data->temp->item != NULL)
			free_ptr((void **)&data->temp->item);
		if (data->temp->map_check != NULL)
			free_matrix(&data->temp->map_check, data->temp->y);
		free(data->temp);
		data->temp = NULL;
	}
}

void	ft_error(char *str, t_data *data)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	if (data != NULL)
	{
		if (data->temp->fd_map != -1)
			manage_file(NULL, data, 'C');
		free_temp(data);
		free_all(data);
	}
	exit(1);
}
