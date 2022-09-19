NAME = cub3d

INC = cub3d.h

CC = cc -Wall -Wextra -Werror

SRC = 	./cub3d.c\
		./src/utils.c\
		./parsing/check_inputs.c

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
	@$(CC) $(OBJ) -o $(NAME)
	@echo "$(COLOUR_GREEN)Executable created (./${NAME})$(COLOUR_END)"

clean:
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re: fclean all
.PHONY : clean fclean re all