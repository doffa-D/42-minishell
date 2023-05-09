# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 12:19:16 by nouakhro          #+#    #+#              #
#    Updated: 2023/05/09 21:59:43 by nouakhro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(DEBUG),1)
	OPTS = -fsanitize=address -g
endif

CC = cc

CCFLAGS = -Wall -Werror -Wextra $(OPTS)

BUILTINS = $(addprefix builtins/,  builtins_in_chiled builtins_in_parent builtins_is_exist bultins_execut_in_parent)
COMMANDE = $(addprefix commande/,  cd_commande commande echo_command env_commd exit export_command partition_commande_by_commande pwd_command split_commande_rederaction unset_command)
EXCUTION = $(addprefix excution/,  calculate_how_many_rederaction_input calculate_how_many_rederaction_output check_rediraction close_and_free environment_creat_linked_list excution_errors get_enviroment init_and_rediraction_is_exist manage_pipe_and_rederaction path_is_exist_or_not pipe_is_exist_or_its_not_builtins readline_return_somthing split_each_argemnt_whithout_parccing split_path syntax_error)
EXPANDE = $(addprefix expande/,  expand_exit_status_and_some_caracters_after_dolar expande_varbles manage_expand_variables parccing_expande_variabls_in_commande)
PARCCING = $(addprefix parccing/,  her_doc_manipulate parccen parccing_part_remve_double_and_single_quotes parccing_rederaction_input_part parccing_rediraction_output_part parccing_represent_pipe_and_rediraction parccing_utils parccing_whith_just_represent remove_quotes_in_rederaction_parccing_part)
UTILS = $(addprefix utils/,  utils_rediraction utils_pwd_commande utils utils_cd_command utils_check_rediractions_chiled utils_check_rediractions_parent utils_check_rediractions_parent_2 utils_exit_commande utils_export_command_1 utils_export_command_2 utils_export_command_3)
FILES    = $(addprefix src/, main $(UTILS) $(PARCCING) $(EXPANDE) $(EXCUTION) $(COMMANDE) $(BUILTINS))

SRC        = $(FILES:=.c)
OBJE        = $(SRC:.c=.o)

NAME = minishell

LIBFT = src/libft

all : $(NAME)

$(NAME) : $(OBJE)
	make -C $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJE) $(LIBFT)/libft.a -lreadline  -o $(NAME)

%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean :
	rm -f $(OBJE)
	make clean -C $(LIBFT)

fclean : clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re:fclean $(NAME)