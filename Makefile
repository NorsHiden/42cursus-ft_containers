# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 15:05:52 by nelidris          #+#    #+#              #
#    Updated: 2023/01/22 18:36:43 by nelidris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -I containers -I utils

SRCS = main.cpp tests/vector_test.cpp tests/map_test.cpp tests/set_test.cpp tests/stack_test.cpp

NAME = intra_main vector_test map_test set_test stack_test

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) main.cpp -o intra_main
	$(CC) $(CFLAGS) tests/vector_test.cpp -o vector_test
	$(CC) $(CFLAGS) tests/map_test.cpp -o map_test
	$(CC) $(CFLAGS) tests/set_test.cpp -o set_test
	$(CC) $(CFLAGS) tests/stack_test.cpp -o stack_test

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re