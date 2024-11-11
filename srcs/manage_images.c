/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:19:45 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 15:14:58 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	update_image(t_data *data)
{
	if (data->map[data->player_y][data->player_x] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->sprite->floor, data->player_x * TILE, data->player_y * TILE);
	if (data->map[data->player_y][data->player_x] == 'P')
		add_player(data, data->player_y, data->player_x);
}

void	assign_all_img(t_data *data)
{
	data->sprite->wall = mlx_xpm_file_to_image(data->mlx_ptr, WALL,
			&data->img_x, &data->img_y);
	data->sprite->floor = mlx_xpm_file_to_image(data->mlx_ptr, FLOOR,
			&data->img_x, &data->img_y);
	data->sprite->player = mlx_xpm_file_to_image(data->mlx_ptr, PLAYER,
			&data->img_x, &data->img_y);
	data->sprite->star = mlx_xpm_file_to_image(data->mlx_ptr, STAR,
			&data->img_x, &data->img_y);
	data->sprite->closed_exit = mlx_xpm_file_to_image(data->mlx_ptr, CLOSED_EXIT,
			&data->img_x, &data->img_y);
	data->sprite->opened_exit = mlx_xpm_file_to_image(data->mlx_ptr, OPENED_EXIT,
			&data->img_x, &data->img_y);
	check_images_alloc(data);
}

void	destroy_all_img(t_data *data)
{
	if (data->sprite != NULL)
	{
		if (data->sprite->wall != NULL)
			mlx_destroy_image(data->mlx_ptr, data->sprite->wall);
		if (data->sprite->floor != NULL)
			mlx_destroy_image(data->mlx_ptr, data->sprite->floor);
		if (data->sprite->player != NULL)
			mlx_destroy_image(data->mlx_ptr, data->sprite->player);
		if (data->sprite->star != NULL)
			mlx_destroy_image(data->mlx_ptr, data->sprite->star);
		if (data->sprite->opened_exit != NULL)
			mlx_destroy_image(data->mlx_ptr, data->sprite->closed_exit);
		if (data->sprite->closed_exit != NULL)
			mlx_destroy_image(data->mlx_ptr, data->sprite->opened_exit);
		free(data->sprite);
		data->sprite = NULL;
	}
}
