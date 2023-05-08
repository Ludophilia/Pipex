# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 14:16:47 by jgermany          #+#    #+#              #
#    Updated: 2023/05/08 17:28:42 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME							:= ../libftprintf.a

CC								:= cc
CFLAGS							:= -Wall -Wextra -Werror

AR								:= ar
ARFL							:= -rcs

ROOT							:= .

LFTDR							:= ../libft
CMDR							:= $(ROOT)/commons
PADR							:= $(ROOT)/parser
PRDR							:= $(ROOT)/printer

LFT								:= $(LFTDR)/libft.a

ROOT_HDR						:= $(ROOT)/ft_dprintf.h
MAN_SRCS						:= $(ROOT)/ft_dprintf.c

CM_HDR							:= $(CMDR)/commons.h
MAN_SRCS						+= $(CMDR)/commons.c

PA_HDR							:= $(PADR)/parser.h
MAN_SRCS						+= $(PADR)/parser.c

PR_HDR							:= $(PRDR)/printer.h
MAN_SRCS						+= $(PRDR)/printer.c

MAN_OBJS						:= $(MAN_SRCS:.c=.o)

all:							$(NAME)


$(NAME):						$(MAN_OBJS) | $(LFT)
								cp $(LFT) $@
								$(AR) $(ARFL) $@ $^

$(LFT):
								make -C $(LFTDR) all

%.o:							$(ROOT_HDR)

commons/%.o:					$(CM_HDR)

parser/%.o:						$(PA_HDR)

printer/%.o:					$(PR_HDR)

clean:
								rm -f $(MAN_OBJS)
								make -C $(LFTDR) clean

fclean:							clean
								rm -f $(NAME)
								make -C $(LFTDR) fclean

re:
								make fclean
								make all

.DELETE_ON_ERROR:
.PHONY:							all clean fclean re
.SILENT:						clean fclean
