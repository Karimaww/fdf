CC			= gcc

NAME		= fdf

SOURCES =	draw_fdf.c		\
			draw_line.c		\
			events.c		\
			get_color.c		\
			hex_to_trgb.c	\
			init_fdf.c		\
			isometric.c		\
			main.c			\
			mlx_utils.c		\
			parsing.c		\
			parsing_utils.c	\

LIBFT		= libft

MLX			= mlx

CFLAGS		= -Wall -Wextra -Werror -g3

INCLUDE		= include

SRC_DIR		= src

OBJ_DIR		= obj

RM			= rm -f

SRC	=	$(addprefix $(SRC_DIR)/,$(SOURCES))
OBJS =	$(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

all: lib obj $(NAME)

bonus: lib obj $(NAME)

lib:
	@make -C $(LIBFT)
	@make -C $(MLX)

obj:
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L $(LIBFT) -L $(MLX) -lmlx -lft -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)/fdf.h $(INCLUDE)/colors.h 
	$(CC) $(CFLAGS) -I $(INCLUDE) -Imlx -c $< -o $@

bonus: $(NAME)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re