# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 21:48:36 by jgermany          #+#    #+#              #
#    Updated: 2023/04/23 20:16:45 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RW_DIR := level0/rw
FL_DIR := level0/fl
ER_DIR := level0/er
FK_DIR := level1/fork
WT_DIR := level1/wait
PI_DIR := level1/pipe
PF_DIR := level2/printf

RW := $(RW_DIR)/rw_ex.c
FL := $(FL_DIR)/fl_ex.c
FK := $(FK_DIR)/fork_ex.c
ER := $(ER_DIR)/er_ex.c
PI := $(PI_DIR)/pipe_ex.c 
PF := $(PF_DIR)/printf_redirect_ex.c
WT := $(WT_DIR)/wait_ex.c

RW_OUT := $(RW:.c=.out)
FK_OUT := $(FK:.c=.out)
FL_OUT := $(FL:.c=.out)
PF_OUT := $(PF:.c=.out)
PI_OUT := $(PI:.c=.out)
ER_OUT := $(ER:.c=.out)
WT_OUT := $(WT:.c=.out)

er: $(ER_OUT)
	./$<

wt: $(WT_OUT)
	./$<

fl: $(FL_OUT)
	./$<

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
	rm -f $(RW_OUT) $(PF_OUT) $(FK_OUT) $(PI_OUT) $(FL_OUT) $(ER_OUT) $(WT_OUT)

re: fclean
	make

.PHONY: pi pf fk rw clean fclean
