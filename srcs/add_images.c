/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:39:54 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 15:06:39 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	add_ground(t_data *data, int y, int x)
{
	if (data->map[y][x] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->sprite->floor, x * TILE, y * TILE);
}

void	add_wall(t_data *data, int y, int x)
{
	if (data->map[y][x] == '1')
	{
		if (y == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->sprite->wall, x * TILE, y * TILE);
		else if (y == data->size_y - 1)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->sprite->wall, x * TILE, y * TILE);
		else if (x == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->sprite->wall, x * TILE, y * TILE);
		else if (x == data->size_x - 1)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->sprite->wall, x * TILE, y * TILE);
		else
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->sprite->wall, x * TILE, y * TILE);
	}
}

void	add_collectible(t_data *data, int y, int x)
{
	if (data->map[y][x] == 'C')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->sprite->star, x * TILE, y * TILE);
	}
}

void	add_player(t_data *data, int y, int x)
{
	if (data->map[y][x] == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->sprite->player, x * TILE, y * TILE);
}

void	add_exit_close(t_data *data, int y, int x)
{
	if (data->map[y][x] == 'E')
	{
		data->exit_y = y;
		data->exit_x = x;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->sprite->closed_exit, x * TILE, y * TILE);
	}
}
