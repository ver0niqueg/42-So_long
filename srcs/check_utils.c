/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:23:42 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 15:08:04 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*
**	manage_file function,
**	'O' to open the file
** 	'C' to close the file.
**
**	temp->line == NULL --> true when file read ends.
*/
int	count_lines(char *argv, t_data *data)
{
	manage_file(argv, data, 'O');
	while (data->temp->fd_map > 0)
	{
		data->temp->line = get_next_line(data->temp->fd_map);
		if (data->temp->line == NULL)
		{
			manage_file(NULL, data, 'C');
			break ;
		}
		if (data->temp->line[0] == '\n' && data->temp->line[1] == '\0')
			return (0);
		data->temp->y++;
		free_ptr((void **)&data->temp->line);
	}
	data->size_y = data->temp->y;
	if (data->temp->y < 3)
		return (0);
	return (1);
}

static void	check_last_line(t_data *data, char *line, int i)
{
	if (i == data->temp->y - 1)
	{
		if (ft_getnl(line) != NULL)
			ft_error("Error\nInvalid map file.\n", data);
	}
}

/*
**	Opening the file with flag 'O',
**	closing the file with flag 'C'.
*/
void	fill_matrix(char *argv, t_data *data, int i)
{
	alloc_matrix(&data->temp->map_check, data);
	manage_file(argv, data, 'O');
	while (i < data->temp->y)
	{
		data->temp->line = get_next_line(data->temp->fd_map);
		check_alloc(data->temp->line, data);
		check_last_line(data, data->temp->line, i);
		data->temp->map_check[i] = ft_strtrim(data->temp->line, "\n");
		check_alloc(data->temp->map_check[i], data);
		data->temp->x = ft_strlen(data->temp->map_check[i]);
		data->size_x = data->temp->x;
		free_ptr((void **)&data->temp->line);
		i++;
	}
	manage_file(NULL, data, 'C');
	alloc_matrix(&data->map, data);
	i = 0;
	while (i < data->temp->y)
	{
		data->map[i] = ft_strdup(data->temp->map_check[i]);
		check_alloc(data->map[i], data);
		i++;
	}
}

void	manage_file(char *argv, t_data *data, int flag)
{
	if (flag == 'O')
	{
		data->temp->fd_map = open(argv, O_RDONLY);
		if (data->temp->fd_map == -1)
			ft_error("Error\nFile issue.\n", data);
	}
	else if (flag == 'C')
	{
		if (data->temp->fd_map != -1)
		{
			close(data->temp->fd_map);
			data->temp->fd_map = -1;
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
