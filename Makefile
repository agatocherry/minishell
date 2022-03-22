# Variables

NAME	=	minishell
CC		=	gcc
#DONT FORGET TO USE -Werror -Wall -Wextra 
CFLAGS	=	-g -c
SRCS	=	src/main.c src/minishell.c src/init.c \
			src/cmd/parsing.c src/cmd/struct.c src/cmd/line.c \
			src/env/parsing.c \
			src/signal/signal.c
OBJ		=	$(SRCS:.c=.o)

# Rules

all: $(NAME)

$(NAME):	$(OBJ)
	@make -C libft/
	@$(CC) $(OBJ) -o $(NAME) libft/libft.a
	@echo "Compiling $(NAME) done"

%.o: %.c
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
