# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:57:02 by jgermany          #+#    #+#              #
#    Updated: 2023/05/11 22:31:45 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc
CFLAGS := -Wall -Wextra -Werror

MAN_SRCS := pipex.c
MAN_SRCS += sanicheck.c

MAN_OBJS := $(MAN_SRCS:.c=.o)

LFTPF := libftprintf.a

all: $(NAME)

bonus: 
	@echo "A friendly reminder that bonuses should be in a different file \
	suffixed _bonus.[ch]"

$(LFTPF):
	make -C ft_dprintf/

$(NAME): $(MAN_OBJS) | $(LFTPF)
	$(CC) $(CFLAGS) $(MAN_OBJS) -o $@ -lftprintf -L.

pipex.o: pipex.h
sanicheck.o: sanicheck.h

clean:
	make -C ft_dprintf/ clean 
	rm -f $(MAN_OBJS)

fclean: clean
	make -C ft_dprintf/ fclean 
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
.SILENT: clean fclean
