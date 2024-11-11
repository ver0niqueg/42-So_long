/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:36:00 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 15:12:33 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	init_temp(t_data *data)
{
	data->temp = ft_calloc(1, sizeof(t_temp));
	check_alloc(data->temp, NULL);
	data->temp->item = ft_calloc(2, sizeof(int));
	check_alloc(data->temp->item, data);
	data->temp->x = 0;
	data->temp->y = 0;
	data->temp->fd_map = -1;
	data->temp->map_check = NULL;
	data->temp->line = NULL;
}

void	init_data(t_data *data)
{
	data->move_counter = 1;
	data->item_count = 0;
	data->item_found = 0;
	data->on_exit = 0;
	data->exit_x = 0;
	data->exit_y = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->size_x = 0;
	data->size_y = 0;
	data->max_x = 0;
	data->max_y = 0;
	data->img_x = 0;
	data->img_y = 0;
	data->map = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->sprite = NULL;
	init_temp(data);
}

void	alloc_matrix(char ***matrix, t_data *data)
{
	*matrix = ft_calloc(data->temp->y, sizeof(char *));
	check_alloc(*matrix, data);
}

void	check_alloc(void *ptr, t_data *data)
{
	if (ptr == NULL)
		ft_error("Error\nMemory allocation failed.\n", data);
}

void	check_images_alloc(t_data *data)
{
	if (!data->sprite->wall || !data->sprite->wall || !data->sprite->floor
		|| !data->sprite->player
		|| !data->sprite->closed_exit
		|| !data->sprite->opened_exit)
	{
		ft_putstr_fd("Error\nMemory allocation failed for images.\n", 2);
		destroy_all(data, 1);
	}
}
