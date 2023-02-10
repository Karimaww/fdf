CC			= gcc

NAME		= fdfbis

SOURCES =	main.c\

LIBFT		= libft

MLX			= mlx

CFLAGS		= -Wall -Wextra -Werror -lm

INCLUDE		= include

SRC_DIR		= src

OBJ_DIR		= obj

RM			= rm -f

SRC	=	$(addprefix $(SRC_DIR)/,$(SOURCES))
OBJS =	$(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

all: lib obj $(NAME)

lib:
	@make -C $(LIBFT)
	@make -C $(MLX)

obj:
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L $(LIBFT) -L $(MLX) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)/fdf.h
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