# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 21:48:36 by jgermany          #+#    #+#              #
#    Updated: 2023/04/14 22:20:43 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RW := rw/read_write_ex.c
FW := fork/fork_ex.c

RW_OUT := $(RW:.c=.out)
FW_OUT := $(FW_OUT:.c=.out)

rw: $(RW_OUT)
	@./$<

%.out: %.c
	@cc $< -o $@

clean: fclean

fclean:
	@rm -f $(RW_OUT)

.PHONY: rw clean fclean