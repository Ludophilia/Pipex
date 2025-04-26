# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jegerman <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:57:02 by jgermany          #+#    #+#              #
#    Updated: 2025/04/26 18:33:16 by jegerman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
BON_NAME := pipex_bonus

CC := cc
CFLAGS := -Wall -Wextra -Werror 

LFT_DR := libs/libft

SRCS_DR := srcs
SRCS_BDR := srcs_bonus

ICL_DR := includes
ICL_BDR := includes_bonus

all: CFLAGS += -I$(ICL_DR)
debug: CFLAGS += -g3
bonus: CFLAGS += -I$(ICL_BDR) 

CFLAGS += -I$(LFT_DR)

MAN_SRCS := $(SRCS_DR)/main.c
MAN_SRCS += $(SRCS_DR)/cmdparser.c
MAN_SRCS += $(SRCS_DR)/filemgr.c
# MAN_SRCS += $(SRCS_DR)/cmdmgr.c
MAN_SRCS += $(SRCS_DR)/sanicheck.c

MAN_OBJS := $(MAN_SRCS:.c=.o)

BON_SRCS := $(SRCS_BDR)/main_bonus.c
BON_SRCS += $(SRCS_BDR)/sanicheck_bonus.c
BON_SRCS += $(SRCS_BDR)/filemgr_bonus.c
BON_SRCS += $(SRCS_BDR)/cmdmgr_bonus.c
BON_SRCS += $(SRCS_BDR)/cmdenvmgr_bonus.c
BON_SRCS += $(SRCS_BDR)/heredocmgr_bonus.c

BON_OBJS := $(BON_SRCS:.c=.o)

LFT := $(LFT_DR)/libft.a

debug: all

all: $(NAME)

bonus: $(BON_NAME)

$(BON_NAME): $(BON_OBJS) | $(LFT)
	$(CC) $(CFLAGS) $(BON_OBJS) -o $@ -lft -L$(LFT_DR)

$(NAME): $(MAN_OBJS) | $(LFT)
	$(CC) $(CFLAGS) $(MAN_OBJS) -o $@ -lft -L$(LFT_DR)

$(LFT):
	make -C $(LFT_DR)

$(SRCS_DR)/%.o: $(ICL_DR)/pipex.h

$(SRCS_BDR)/%_bonus.o: $(ICL_BDR)/pipex_bonus.h

clean:
	make -C $(LFT_DR) clean
	rm -f $(MAN_OBJS) $(BON_OBJS)

fclean: clean
	make -C $(LFT_DR) fclean
	rm -f $(NAME) $(BON_NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT: clean fclean
