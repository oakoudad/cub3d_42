NAME = cub3d

INC = cub3d.h

CC = cc -Wall -Wextra -Werror

SRC = 	./cub3d.c\
		./src/numbers.c\
		./src/string.c\
		./src/utils.c\
		./src/ft_split.c\
		./parsing/check_inputs.c\
		./parsing/check_map.c\
		./parsing/map.c\
		./raycasting/raycasting.c\
		./raycasting/raying.c\
		./parsing/check_map_utils.c\
		./gnl/get_next_line.c\
		./gnl/get_next_line_utils.c\
		./math/math.c\
		./raycasting/texture.c\

OBJ = $(SRC:.c=.o)

COLOUR_GREEN=\033[0;32m
COLOUR_YELLOW=\033[0;33m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

%.o : %.c
	@echo "Create $(COLOUR_BLUE)$@$(COLOUR_END) from $(COLOUR_YELLOW)$<$(COLOUR_END)"
	@$(CC) -c $< -o $@

all : $(NAME)

$(NAME) : $(INC)  $(OBJ)
	# @$(CC) $(OBJ) -o $(NAME) -L.. -lmlx -L%%%%/../lib -lXext -lX11 -lm -lbsd
	@$(CC) $(OBJ) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@echo "$(COLOUR_GREEN)Executable created (./${NAME})$(COLOUR_END)"

clean:
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re: fclean all
.PHONY : clean fclean re all