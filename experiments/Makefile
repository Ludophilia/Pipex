# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 21:48:36 by jgermany          #+#    #+#              #
#    Updated: 2023/04/15 00:37:50 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RW := rw/read_write_ex.c
FK := fork/fork_ex.c
PF := printf/printf_redirect_ex.c

RW_OUT := $(RW:.c=.out)
FK_OUT := $(FK:.c=.out)
PF_OUT := $(PF:.c=.out)

all: pf #rw

pf: $(PF_OUT)
	./$<

rw: $(RW_OUT)
	./$<

%.out: %.c %.h
	cc $< -o $@

%.out: %.c
	cc $< -o $@

clean:
	rm -f rw/regular_file

fclean: clean
	rm -f $(RW_OUT)
	rm -f $(PF_OUT)

re: fclean
	make all

.PHONY: all rw clean fclean
