# Variables

NAME	=	minishell
CC		=	gcc
#DONT FORGET TO USE -Werror -Wall -Wextra 
CFLAGS	=	-g -c
SRCS	=	src/main.c
OBJ		=	$(SRCS:.c=.o)

# Rules

all: $(NAME)

$(NAME):	$(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "Compiling $(NAME) done"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJ)
	@echo "! Removed $(OBJ)"

fclean: clean
	@rm -rf $(NAME)
	@echo "! Removed $(NAME)"

re: fclean all