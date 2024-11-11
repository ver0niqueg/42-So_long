/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:11:34 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/11 20:26:17 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdbool.h>

# define BUFFER_SIZE 1
# define TILE 64
# define WALL "./sprites/wall.xpm"
# define FLOOR "./sprites/floor.xpm"
# define PLAYER "./sprites/player.xpm"
# define STAR "./sprites/star.xpm"
# define OPENED_EXIT "./sprites/opened_exit.xpm"
# define CLOSED_EXIT "./sprites/closed_exit.xpm"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define GREY "\033[90m"
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

typedef struct s_game
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
}				t_game;

/* INPUT CHECKS + MAP CHECKS */
char			*get_next_line(int fd);
char			*ft_getnl(char *str);
int				check_path(t_game *game);
int				count_lines(char *argv, t_game *game);
int				is_map_valid(char *argv, t_game *game);
int				check_map_extension(char *argv);

/* INIT SPRITES */
void			add_floor(t_game *game, int y, int x);
void			add_wall(t_game *game, int y, int x);
void			add_collectible(t_game *game, int i, int j);
void			add_player(t_game *game, int i, int j);
void			add_closed_exit(t_game *game, int i, int j);
void			add_sprites_to_map(t_game *game, int y, int x);
void			update_sprite(t_game *game);
void			assign_all_sprites(t_game *game);

/* INIT GAME */
void			alloc_matrix(char ***matrix, t_game *game);
void			check_alloc(void *ptr, t_game *game);
void			init_data(t_game *game);
void			fill_matrix(char *argv, t_game *game, int i);

/* MANAGEMENT */
void			free_temp(t_game *game);
void			free_all(t_game *game);
void			free_matrix(char ***matrix, int y);
void			free_ptr(void **ptr);
void			ft_error(char *str, t_game *game);
void			manage_file(char *argv, t_game *game, int flag);
void			check_sprites_alloc(t_game *game);
void			destroy_all_sprites(t_game *game);
void			destroy_all(t_game *game, int error);

/* START GAME */
int				close_game(t_game *game);
int				handle_keypress(int keycode, t_game *game);

#endif
