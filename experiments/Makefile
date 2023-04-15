# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 21:48:36 by jgermany          #+#    #+#              #
#    Updated: 2023/04/15 16:39:03 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RW_DIR := level0/rw
FK_DIR := level1/fork
PI_DIR := level1/pipe
PF_DIR := level2/printf

RW := $(RW_DIR)/rw_ex.c
FK := $(FK_DIR)/fork_ex.c
PI := $(PI_DIR)/pipe_ex.c 
PF := $(PF_DIR)/printf_redirect_ex.c

RW_OUT := $(RW:.c=.out)
FK_OUT := $(FK:.c=.out)
PF_OUT := $(PF:.c=.out)
PI_OUT := $(PI:.c=.out)

pf: $(PF_OUT)
	./$<

pi: $(PI_OUT)
	./$<

rw: $(RW_OUT)
	./$<

fk: $(FK_OUT)
	./$<

%.out: %.c %.h
	cc $< -o $@

%.out: %.c
	cc $< -o $@

clean:
	rm -f $(RW_DIR)/regular_file

fclean: clean
	rm -f $(RW_OUT) $(PF_OUT) $(FK_OUT) $(PI_OUT)

re: fclean
	make all

.PHONY: pi pf fk rw clean fclean
