# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 22:44:05 by shdorlin          #+#    #+#              #
#    Updated: 2021/11/25 11:39:11 by shdorlin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
AR = ar
HEADER = libft.h
CFLAGS = -Wall -Wextra -Werror
ARFLAGS = rc
SRCS = $(filter-out $(wildcard ft_lst*.c), $(wildcard *.c))
OBJS = $(SRCS:.c=.o)
BONUS = $(wildcard ft_lst*.c)
OBJS_B = $(BONUS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) 

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS_B)
	$(AR) $(ARFLAGS) $(NAME) *.o

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all
