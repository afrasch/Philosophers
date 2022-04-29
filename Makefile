# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 15:22:48 by afrasch           #+#    #+#              #
#    Updated: 2022/04/28 15:47:18 by afrasch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CFLAGS	= -Wall -Wextra -Werror

LIBS	= -pthreads

CC		= cc

SRC		= arrival.c enter_the_gate.c grow_beards.c start_the_banquet.c \
		the_routine.c stop_the_banquet.c mini_libft_1.c mini_libft_2.c \
		announcer.c \

OBJ		= $(SRC:.c=.o)

HEADER	= philo.h

RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
