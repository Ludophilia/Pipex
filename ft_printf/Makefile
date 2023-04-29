# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 14:16:47 by jgermany          #+#    #+#              #
#    Updated: 2023/04/29 14:03:40 by jgermany         ###   ########.fr        #
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
WRDR							:= $(ROOT)/writer

LFT								:= $(LFTDR)/libft.a

ROOT_HDR						:= $(ROOT)/ft_printf.h
MAN_SRCS						:= $(ROOT)/ft_printf.c
ROOT_HDR_BON					:= $(ROOT)/ft_printf_bonus.h
BON_SRCS						:= $(ROOT)/ft_printf_bonus.c

CM_HDR							:= $(CMDR)/commons.h
MAN_SRCS						+= $(CMDR)/commons.c
CM_HDR_BON						:= $(CMDR)/commons_bonus.h
BON_SRCS						+= $(CMDR)/commons.c
BON_SRCS						+= $(CMDR)/commons_lists_bonus.c

PA_HDR							:= $(PADR)/parser.h
MAN_SRCS						+= $(PADR)/parser.c
PA_HDR_BON						:= $(PADR)/parser_bonus.h
BON_SRCS						+= $(PADR)/parser_bonus.c
BON_SRCS						+= $(PADR)/parser_checkers_bonus.c
BON_SRCS						+= $(PADR)/parser_helpers_bonus.c

PR_HDR							:= $(PRDR)/printer.h
MAN_SRCS						+= $(PRDR)/printer.c
PR_HDR_BON						:= $(PRDR)/printer_bonus.h
BON_SRCS						+= $(PRDR)/printer_bonus.c
BON_SRCS						+= $(PRDR)/printer_checkers_bonus.c
BON_SRCS						+= $(PRDR)/printer_helpers_bonus.c

WR_HDR_BON						:= $(WRDR)/writer_bonus.h
BON_SRCS						+= $(WRDR)/writer_bonus.c

MAN_OBJS						:= $(MAN_SRCS:.c=.o)
BON_OBJS						:= $(BON_SRCS:.c=.o)

all:							$(NAME)

bonus:							$(BON_OBJS) | $(LFT) 
								cp $(LFT) $(NAME)
								$(AR) $(ARFL) $(NAME) $^

$(NAME):						$(MAN_OBJS) | $(LFT)
								cp $(LFT) $@
								$(AR) $(ARFL) $@ $^

$(LFT):
								make -C $(LFTDR) all
								make -C $(LFTDR) bonus

%.o:							$(ROOT_HDR)
%_bonus.o:						$(ROOT_HDR_BON)

commons/%.o:					$(CM_HDR)
commons/%_bonus.o:				$(CM_HDR_BON)

parser/%.o:						$(PA_HDR)
parser/%_bonus.o:				$(PA_HDR_BON)

printer/%.o:					$(PR_HDR)
printer/%_bonus.o:				$(PR_HDR_BON)

writer/%_bonus.o:				$(WR_HDR_BON)

clean:
								rm -f $(MAN_OBJS) $(BON_OBJS)
								make -C $(LFTDR) clean

fclean:							clean
								rm -f $(NAME)
								make -C $(LFTDR) fclean

re:
								make fclean
								make all

.DELETE_ON_ERROR:
.PHONY:							all bonus clean fclean re
.SILENT:						clean fclean
