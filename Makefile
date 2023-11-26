# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:57:02 by jgermany          #+#    #+#              #
#    Updated: 2023/11/26 14:40:57 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
BON_NAME := pipex_bonus

CC := cc
CFLAGS := -Wall -Wextra -Werror

LIBS_DR := libs
SRCS_DR := srcs
SRCS_BDR := srcs_bonus
ICL_DR := includes
ICL_BDR := includes_bonus

all: CFLAGS += -I$(ICL_DR) -I$(LIBS_DR)
bonus: CFLAGS += -I$(ICL_BDR) -I$(LIBS_DR)

MAN_SRCS := $(SRCS_DR)/pipex.c
MAN_SRCS += $(SRCS_DR)/sanicheck.c
MAN_SRCS += $(SRCS_DR)/filemgr.c
MAN_SRCS += $(SRCS_DR)/cmdmgr.c
MAN_SRCS += $(SRCS_DR)/cmdenvmgr.c

MAN_OBJS := $(MAN_SRCS:.c=.o)

BON_SRCS := $(SRCS_BDR)/pipex_bonus.c
BON_SRCS += $(SRCS_BDR)/sanicheck_bonus.c
BON_SRCS += $(SRCS_BDR)/filemgr_bonus.c
BON_SRCS += $(SRCS_BDR)/cmdmgr_bonus.c
BON_SRCS += $(SRCS_BDR)/cmdenvmgr_bonus.c
BON_SRCS += $(SRCS_BDR)/heredocmgr_bonus.c

BON_OBJS := $(BON_SRCS:.c=.o)

LFTPF := $(LIBS_DR)/libftprintf.a

all: $(NAME)

bonus: $(BON_OBJS) | $(LFTPF)
	$(CC) $(CFLAGS) $(BON_OBJS) -o $(BON_NAME) -lftprintf -L$(LIBS_DR)

$(LFTPF):
	make -C $(LIBS_DR)/ft_dprintf

$(NAME): $(MAN_OBJS) | $(LFTPF)
	$(CC) $(CFLAGS) $(MAN_OBJS) -o $@ -lftprintf -L$(LIBS_DR)

$(SRCS_DR)/%.o: $(ICL_DR)/%.h $(ICL_DR)/commonlibs.h

$(SRCS_BDR)/%_bonus.o: $(ICL_BDR)/%_bonus.h $(ICL_BDR)/commonlibs_bonus.h

clean:
	make -C $(LIBS_DR)/ft_dprintf clean
	rm -f $(MAN_OBJS) $(BON_OBJS)

fclean: clean
	make -C $(LIBS_DR)/ft_dprintf fclean
	rm -f $(NAME) $(BON_NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
.SILENT: clean fclean
