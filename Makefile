# Variables

NAME	=	minishell
HEADER	=	include/minishell.h
CC		=	gcc
#DONT FORGET TO USE -Werror -Wall -Wextra 
CFLAGS	=	-g -c -Werror -Wall -Wextra
SRCS	=	src/main/main.c src/main/minishell.c src/main/signal.c \
			src/init/init.c \
			src/utils/clear.c \
			src/cmd/parsing.c src/cmd/struct.c src/cmd/line.c src/cmd/expansion.c \
			src/env/parsing.c \
OBJ		=	$(SRCS:.c=.o)

# Rules

all: $(NAME)

$(NAME):	$(OBJ) $(HEADER)
	@make -C libft/
	@$(CC) $(OBJ) -o $(NAME) $(HEADER) libft/libft.a
	@echo "Compiling $(NAME) done"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJ)
	@make clean -C libft/
	@echo "! Removed $(OBJ)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft/
	@echo "! Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
