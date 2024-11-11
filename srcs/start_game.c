/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:23:00 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 17:14:32 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	destroy_all(t_data *data, int error)
{
	destroy_all_img(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_loop_end(data->mlx_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free_all(data);
	if (error == 1)
		exit(1);
	else
	{
		ft_printf("Thank you for playing!\n");
		exit(0);
	}
}

static void	add_exit_open(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->sprite->opened_exit,
		data->exit_x * TILE, data->exit_y * TILE);
}

void	move_player(t_data *data, int y, int x)
{
	static int	is_exit_open = 0;

	if (data->map[y][x] == '1')
		return ;
	if (data->map[y][x] == 'C')
		data->item_found++;
	if (data->map[y][x] == 'E' && data->item_found != data->item_count)
	{
		ft_printf("You must collect all the items first!\n");
		return ;
	}
	if (data->map[y][x] == 'E' && data->item_found == data->item_count)
	{
		data->on_exit = 1;
		return ;
	}
	if (data->item_found == data->item_count && is_exit_open++ == 0)
		add_exit_open(data);
	data->map[data->player_y][data->player_x] = '0';
	update_image(data);
	data->player_y = y;
	data->player_x = x;
	data->map[data->player_y][data->player_x] = 'P';
	update_image(data);
	ft_printf("Movements : %d\n", data->move_counter++);
}

int	on_keypress(int keycode, t_data *data)
{
	int	y;
	int	x;

	y = data->player_y;
	x = data->player_x;
	if (keycode == XK_Escape)
		close_game(data);
	if (keycode == XK_w)
		move_player(data, y - 1, x);
	else if (keycode == XK_s)
		move_player(data, y + 1, x);
	else if (keycode == XK_a)
		move_player(data, y, x - 1);
	else if (keycode == XK_d)
		move_player(data, y, x + 1);
	if (data->on_exit == 1)
	{
		ft_printf("Moves : %d\n", data->move_counter);
		ft_printf("You win !\n");
		close_game(data);
	}
	return (0);
}

void	add_images_to_map(t_data *data, int y, int x)
{
	data->sprite = ft_calloc(1, sizeof(t_sprite));
	if (data->sprite == NULL)
	{
		ft_putstr_fd("Error\nMemory allocation failed.\n", 2);
		destroy_all(data, 1);
	}
	assign_all_img(data);
	while (y < data->size_y)
	{
		x = 0;
		while (x < data->size_x)
		{
			add_ground(data, y, x);
			add_wall(data, y, x);
			add_collectible(data, y, x);
			add_player(data, y, x);
			add_exit_close(data, y, x);
			x++;
		}
		y++;
	}
}
