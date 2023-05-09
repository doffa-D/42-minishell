NAME		= minishell
	
CC		= cc
CFLAGS	+= -Wall -Wextra -Werror
RM		= rm -rf

UTILS		= $(addprefix main/, main)

SRC		= $(UTILS:=.c)
OBJ		= $(UTILS:=.o)


.PHONY: all clean fclean re  norm

all: $(NAME)

$(NAME):  $(OBJ)
	@ $(CC) $(OBJ) -o $(NAME)

%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ $(RM) $(OBJ)


fclean: clean
	@ $(RM) $(NAME)


re: fclean all