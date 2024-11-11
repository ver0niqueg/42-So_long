NAME = so_long

SRCS_DIR = ./srcs/
LIBFT_DIR = ./libft/
MLX_DIR = ./mlx/

LIBFT = $(LIBFT_DIR)/libft.a
MLX = -L$(MLX_DIR)/libmlx.a

CC = cc
RM = rm -f

C_FLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

SRCS =  $(SRCS_DIR)/add_images.c			\
		$(SRCS_DIR)/check_input.c		\
		$(SRCS_DIR)/check_path.c		\
		$(SRCS_DIR)/check_utils.c		\
		$(SRCS_DIR)/error_free.c		\
		$(SRCS_DIR)/get_next_line.c		\
		$(SRCS_DIR)/init_utils.c		\
		$(SRCS_DIR)/manage_images.c		\
		$(SRCS_DIR)/start_game.c		\
		$(SRCS_DIR)/so_long.c			\

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(C_FLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "\n\033[1;32m----------- SO_LONG COMPILED --------------\033[0m\n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	@echo "\n\033[1;32m----------- LIBFT COMPILED -----------------\033[0m\n"

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\n\033[1;38;5;33m----------- CLEANUP ----------------------\033[0m\n"
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\n\033[1;38;5;33m----------- CLEANUP COMPLETE -------------\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
