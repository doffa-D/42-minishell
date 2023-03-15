# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/02 14:47:33 by nouakhro          #+#    #+#              #
#    Updated: 2023/03/14 15:45:30 by nouakhro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILS = 	ft_atoi.c\
		ft_bzero.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memset.c\
		ft_strchr.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_memmove.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_itoa.c\
		ft_strtrim.c\
		ft_split.c \
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\

FILS_BOUNUS = 	ft_lstadd_front.c\
				ft_lstnew.c\
				ft_lstclear.c\
				ft_lstdelone.c\
				ft_lstsize.c\
				ft_lstadd_back.c\
				ft_lstlast.c\
				ft_lstiter.c\
				ft_lstmap.c

GC = gcc
GCFLAGS = -Wall -Werror -Wextra
OBJE= $(FILS:.c=.o)
OBJE_BOUNUS = $(FILS_BOUNUS:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME) : $(OBJE)
	ar -rcs $@ $^

%.o:%.c
	$(GC) $(GCFLAGS) -c $^

clean :
	rm -rf $(OBJE) $(OBJE_BOUNUS)

fclean : clean
	rm -rf $(NAME)
	
re:fclean $(NAME) 

bonus : $(OBJE_BOUNUS)
	ar -rcs $(NAME) $^
