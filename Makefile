NAME = cub3d
CC = cc
CFLAGS = #Wall -Wextra -Werror
LFLAGS = -Lmlx_linux -L./lib -lXext -lX11 -lm
INCLUDES = -Imlx_linux

SRC = main.c \
      parse_map.c \
      get_next_line.c \
      get_next_line_utils.c \
      parsing.c

OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) $(LFLAGS) $(INCLUDES) -o $(NAME)
	@echo "Cub3D is ready!"

$(LIBFT):
	@make -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
