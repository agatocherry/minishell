# Variables

CC		=	gcc
CFLAGS	=	-c -Wall -Werror -Wextra
NAME	=	pipex
SRC		=	src/paths.c src/pipex.c src/execute.c \
			src/error.c src/files.c src/garbage.c src/parsing.c \
			src/ft_split.c src/utils_second.c src/utils.c
OBJ		= $(SRC:.c=.o)

# Rules

all: $(NAME)

$(NAME):	$(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "Compiling $(NAME) done"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@echo "! Removed $(NAME)"

re: fclean all