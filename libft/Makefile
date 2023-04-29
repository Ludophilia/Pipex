# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 13:02:44 by jgermany          #+#    #+#              #
#    Updated: 2022/12/29 18:29:33 by jgermany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

CC 			= cc
CCFL 		= -Wall -Wextra -Werror

INCDIR 		= .
LIB 		= ft
LIBDIR 		= .

CM 			= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
			ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
OBM 		= $(CM:.c=.o)
CB 			= ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
			ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c \
			ft_lstsize_bonus.c
OBB 		= $(CB:.c=.o)

AR 			= ar
ARFLM 		= -rcs
ARFLB 		= -rcs

UNAME 		= $(shell uname -s)
ifeq 		($(UNAME), Linux)
	VG 		= valgrind
	VGFL 	= --leak-check=full --show-leak-kinds=all --track-origins=yes 
endif

all: 		$(NAME)

$(NAME): 	$(OBM)
			$(AR) $(ARFLM) $@ $^
bonus: 		$(OBB)
			$(AR) $(ARFLB) $(NAME) $^

%.o: 		%.c
			$(CC) $(CCFL) -I$(INCDIR) -c $< -o $@
test_%: 	all
			@$(CC) $(CCFL) -I$(INCDIR) tests/$@.c -l$(LIB) -L$(LIBDIR)
			@./a.out
mtest_%:	test_%
			$(VG) $(VGFL) ./a.out

so:
			$(CC) $(CCFL) -fPIC -I$(INCDIR) -c $(CM) $(CB)
			$(CC) $(CCFL) -shared -o libft.so $(OBM) $(OBB)
	
re: 		fclean all
fclean: 	clean
			@-rm -f $(NAME)
clean:
			@rm -f $(OBM)
			@rm -f $(OBB)
			@rm -f $(wildcard *.so)
			@rm -f $(wildcard *.out)

.PHONY: 	all bonus re fclean clean
