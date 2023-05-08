# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 12:19:16 by nouakhro          #+#    #+#              #
#    Updated: 2023/05/08 14:03:43 by nouakhro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(d),1)
	g = -fsanitize=address -g
endif

CC = cc

CCFLAGS = -Wall -Werror -Wextra $(g)

SRC = 	main.c\
		utils.c\
		free_all.c\
		check_rediraction.c\
		commande.c\
		parccen.c\
		echo_command.c\
		env_commd.c\
		export_command.c\
		unset_command.c\
		utils_export_command_1.c\
		utils_export_command_2.c\
		utils_export_command_3.c\
		pwd_command.c\
		pipe_and_rederaction.c\
		cd_commande.c\
		utils_cd_command.c\
		builtins_in_chiled.c\
		builtins_in_parent.c\
		builtins_is_exist.c\
		bultins_execut_in_parent.c\
		close_and_free.c\
		environment_creat_linked_list.c\
		excution_errors.c\
		exit.c\
		get_enviroment.c\
		manage_pipe_and_rederaction.c\
		parccing_represent_pipe_and_rediraction.c\
		parccing_whith_just_represent.c\
		partition_commande_by_commande.c\
		path_is_exist_or_not.c\
		pipe_is_exist_or_its_not_builtins.c\
		readline_return_somthing.c\
		split_each_argemnt_whithout_parccing.c\
		split_path.c\
		utils_exit_commande.c\
		



		
		

OBJE = $(SRC:.c=.o)

NAME = minishell

LIBFT = libft

all : $(NAME)

$(NAME) : $(OBJE)
	make -C $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJE) libft/libft.a -lreadline  -o $(NAME)
# $(CC) $(CCFLAGS) $(OBJE) libft/libft.a -lreadline -L  readline/lib -I readline/include -o $(NAME)

%.o : %.c
	$(CC) $(CCFLAGS) -c $<

clean :
	rm -f $(OBJE)
	make clean -C $(LIBFT)
fclean : clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
re:fclean $(NAME)

run : all
	mv $(OBJE) object && ./minishell