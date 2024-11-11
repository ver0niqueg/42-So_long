/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:11:34 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 15:31:41 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h> // O_RDONLY
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdbool.h>

# define BUFFER_SIZE 1
# define TILE 32
# define WALL "./sprites/wall.xpm"
# define FLOOR "./sprites/floor.xpm"
# define PLAYER "./sprites/player.xpm"
# define STAR "./sprites/star.xpm"
# define OPENED_EXIT "./sprites/opened_exit.xpm"
# define CLOSED_EXIT "./sprites/closed_exit.xpm"

# define RED "\033[31m"
# define GREY "\033[90m"
# define VIOLET "\033[35m"
# define RESET "\033[0m"

typedef struct s_temp
{
	int			x;
	int			y;
	int			fd_map;
	int			*item;
	char		*line;
	char		**map_check;
}				t_temp;

typedef struct s_sprite
{
	void		*wall;
	void		*floor;
	void		*player;
	void		*star;
	void		*opened_exit;
	void		*closed_exit;
}				t_sprite;

typedef struct s_data
{
	int			move_counter;
	int			item_count;
	int			item_found;
	int			player_x;
	int			player_y;
	int			on_exit;
	int			exit_x;
	int			exit_y;
	int			max_x;
	int			max_y;
	int			size_x;
	int			size_y;
	int			img_x;
	int			img_y;
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_temp		*temp;
	t_sprite	*sprite;
}				t_data;

/* INPUT & MAP CHECKS */
char			*get_next_line(int fd);
char			*ft_getnl(char *str);
int				check_path(t_data *data);
int				count_lines(char *argv, t_data *data);
int				is_map_valid(char *argv, t_data *data);
int				check_extension(char *argv);

/* INITIALIZATION */
void			alloc_matrix(char ***matrix, t_data *data);
void			check_alloc(void *ptr, t_data *data);
void			init_data(t_data *data);
void			fill_matrix(char *argv, t_data *data, int i);

/* MANAGEMENT */
void			free_temp(t_data *data);
void			free_all(t_data *data);
void			free_matrix(char ***matrix, int y);
void			free_ptr(void **ptr);
void			ft_error(char *str, t_data *data);
void			manage_file(char *argv, t_data *data, int flag);
void			check_images_alloc(t_data *data);
void			destroy_all_img(t_data *data);
void			destroy_all(t_data *data, int error);

/* START GAME */
int				close_game(t_data *data);
int				on_keypress(int keycode, t_data *data);

/* IMAGES INIT */
void			add_ground(t_data *data, int y, int x);
void			add_wall(t_data *data, int y, int x);
void			add_collectible(t_data *data, int i, int j);
void			add_player(t_data *data, int i, int j);
void			add_exit_close(t_data *data, int i, int j);
void			add_images_to_map(t_data *data, int y, int x);
void			update_image(t_data *data);
void			assign_all_img(t_data *data);

#endif
