# Variables

NAME	=	minishell
HEADER	=	include/minishell.h
CC		=	gcc
#DONT FORGET TO USE -Werror -Wall -Wextra 
CFLAGS	=	lreadline -g -c -Werror -Wall -Wextra 
SRCS	=	src/main.c src/minishell.c src/signal.c \
			src/init.c \
			src/clear.c \
			src/cmd_parsing.c src/cmd_struct.c src/cmd_line.c src/expansion.c \
			src/env.c
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
