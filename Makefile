# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:57:02 by jgermany          #+#    #+#              #
#    Updated: 2023/06/07 21:44:44 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc
CFLAGS := -Wall -Wextra -Werror

MAN_SRCS := pipex.c
MAN_SRCS += sanicheck.c
MAN_SRCS += filemgr.c
MAN_SRCS += cmdmgr.c
MAN_SRCS += cmdenvmgr.c

BON_SRCS := pipex_bonus.c
BON_SRCS += sanicheck_bonus.c
BON_SRCS += filemgr_bonus.c
BON_SRCS += cmdmgr_bonus.c
BON_SRCS += cmdenvmgr_bonus.c

MAN_OBJS := $(MAN_SRCS:.c=.o)
BON_OBJS := $(BON_SRCS:.c=.o)

LFTPF := libftprintf.a

all: $(NAME)

bonus: $(BON_OBJS) | $(LFTPF)
	$(CC) $(CFLAGS) $(BON_OBJS) -o $(NAME) -lftprintf -L.

$(LFTPF):
	make -C ft_dprintf/

$(NAME): $(MAN_OBJS) | $(LFTPF)
	$(CC) $(CFLAGS) $(MAN_OBJS) -o $@ -lftprintf -L.

%.o: %.h commonlibs.h
%_bonus.o: %_bonus.h commonlibs_bonus.h

clean:
	make -C ft_dprintf/ clean
	rm -f $(MAN_OBJS) $(BON_OBJS)

fclean: clean
	make -C ft_dprintf/ fclean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
.SILENT: clean fclean
