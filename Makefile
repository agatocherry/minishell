# Variables

NAME	=	minishell
HEADER	=	./include/minishell.h
LIBFT	=	-L libft -lft
CC		=	gcc
CFLAGS	= 	-Wall -Werror -Wextra -I include/ 
SRCS	=	src/main.c src/minishell.c src/signal.c \
			src/init.c \
			src/clear.c \
			src/cmd_parsing.c src/cmd_struct.c src/cmd_line.c src/expansion.c src/expand_line.c \
			src/cmd_line_2.c src/split_cmd.c \
			src/env.c src/env_2.c \
			src/exec.c src/exec_all.c src/redir.c src/redir_2.c src/utils.c src/pipe.c \
			src/builtins/ft_cd.c src/builtins/ft_cd_utils.c src/builtins/ft_pwd.c src/builtins/ft_echo.c src/builtins/ft_env.c src/builtins/ft_unset.c \
			src/builtins/ft_exit.c src/builtins/ft_export.c src/exec_utils.c
OBJ		=	$(SRCS:.c=.o)

# Rules

all: $(NAME)

$(NAME):	$(OBJ) $(HEADER)
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -lreadline
	@echo "Compiling $(NAME) done"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -o $@ -c $< -lreadline

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

